// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/BASettingsWidgetBase.h"

#include "Components/CheckBox.h"
#include "GameFramework/GameUserSettings.h"
#include "Components/ComboBoxString.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Widgets/BASelectionBase.h"
#include "Widgets/Framerate.h"

namespace
{
	constexpr EFramerate FramerateOptions[] ={
		EFramerate::FPS_30,
		EFramerate::FPS_60,
		EFramerate::FPS_120,
		EFramerate::FPS_Uncapped,
	};

	typedef int32(UGameUserSettings::*GetFunc)() const;
	typedef void(UGameUserSettings::*SetFunc)(int);
	struct FSelectionElement
	{
		UBASelectionBase* Widget;
		GetFunc GetFun;
		SetFunc SetFun;
	};
}

void UBASettingsWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	GameUserSettings=UGameUserSettings::GetGameUserSettings();

	InitializeResolutionComboBox();
	InitializeVSync();
	InitializeFramerate();

	const FSelectionElement SelectionElements[] ={
		{ShadingQualitySelection, &UGameUserSettings::GetShadingQuality, &UGameUserSettings::SetShadingQuality},
		{GlobalIlluminationQualitySelection, &UGameUserSettings::GetGlobalIlluminationQuality, &UGameUserSettings::SetGlobalIlluminationQuality},
		{PostProcessingQualitySelection, &UGameUserSettings::GetPostProcessingQuality, &UGameUserSettings::SetPostProcessingQuality},
		{VisualEffectsQualitySelection, &UGameUserSettings::GetVisualEffectQuality, &UGameUserSettings::SetVisualEffectQuality},
		{TextureQualitySelection,&UGameUserSettings::GetTextureQuality,&UGameUserSettings::SetTextureQuality}
	};
	
	
	for (const auto& [Widget, GetFunc, SetFunc] : SelectionElements)
	{
		const auto CurrentSelection= std::invoke(GetFunc,GameUserSettings);
		Widget->SetCurrentSelection(CurrentSelection);
		Widget->OnSelectionChanged.BindLambda([this, SetFunc](int32 InSelection)
		{
			std::invoke(SetFunc,GameUserSettings,InSelection);
			GameUserSettings->ApplySettings(true);
		});
		
	}
	
}

void UBASettingsWidgetBase::InitializeResolutionComboBox()
{
	Resolutions.Reset();
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(Resolutions);

	ResolutionComboBox->ClearOptions();
	for (const auto& Resolution : Resolutions)
	{
		const auto ResolutionString=FString::Printf(TEXT("%dx%d"), Resolution.X, Resolution.Y);
		ResolutionComboBox->AddOption(ResolutionString);
	}

	const auto CurrentResolution = GameUserSettings->GetScreenResolution();
	const auto SelectedIndex=Resolutions.IndexOfByPredicate(
		[&CurrentResolution](const FIntPoint& InResolution)
		{
			return InResolution==CurrentResolution;
		}
	);
	check(SelectedIndex>=0);
	ResolutionComboBox->SetSelectedIndex(SelectedIndex);

	ResolutionComboBox->OnSelectionChanged.Clear();
	ResolutionComboBox->OnSelectionChanged.AddDynamic(this, &UBASettingsWidgetBase::OnResolutionChanged);
}

void UBASettingsWidgetBase::InitializeVSync()
{
	VSyncCheckBox->SetIsChecked((GameUserSettings->IsVSyncEnabled()));
	VSyncCheckBox->OnCheckStateChanged.Clear();
	VSyncCheckBox->OnCheckStateChanged.AddDynamic(this, &UBASettingsWidgetBase::OnVSyncChanged);
}

void UBASettingsWidgetBase::InitializeFramerate()
{
	int32 FramerateOptionIndex=0;
	
	const auto CurrentFramerate=GameUserSettings->GetFrameRateLimit();
	for (const auto& Framerate : FramerateOptions)
	{
		FramerateSelection->AddOption({
			FText::FromString(FFramerateUtils::EnumToString(Framerate))
		});

		if (CurrentFramerate==FFramerateUtils::EnumToValue(Framerate))
		{
			FramerateSelection->SetCurrentSelection(FramerateOptionIndex);
		}

		FramerateOptionIndex++;
	}

	FramerateSelection->OnSelectionChanged.BindLambda([this](const int32 InSelection)
	{
		GameUserSettings->SetFrameRateLimit(FFramerateUtils::EnumToValue(
			FramerateOptions[InSelection]
		));
		GameUserSettings->ApplySettings(true);
	});
}

void UBASettingsWidgetBase::OnResolutionChanged(FString InSelectedItem, ESelectInfo::Type InSelectionType)
{
	const auto SelectedResolution = Resolutions[ResolutionComboBox->GetSelectedIndex()];
	GameUserSettings->SetScreenResolution(SelectedResolution);
	GameUserSettings->ApplySettings(true);
}

void UBASettingsWidgetBase::OnVSyncChanged(bool InIsChecked)
{
	GameUserSettings->SetVSyncEnabled(InIsChecked);
	GameUserSettings->ApplySettings(true);
}



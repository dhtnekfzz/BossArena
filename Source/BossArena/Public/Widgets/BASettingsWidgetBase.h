// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/BAWidgetBase.h"
#include "BASettingsWidgetBase.generated.h"

class UBASelectionBase;
class UCheckBox;
class UComboBoxString;
/**
 * 
 */
UCLASS()
class BOSSARENA_API UBASettingsWidgetBase : public UBAWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	void InitializeResolutionComboBox();
	void InitializeVSync();
	void InitializeFramerate();

	UFUNCTION()
	void OnResolutionChanged(FString InSelectedItem, ESelectInfo::Type InSelectionType);

	UFUNCTION()
	void OnVSyncChanged(bool InIsChecked);

	UPROPERTY()
	TObjectPtr<UGameUserSettings> GameUserSettings;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UComboBoxString> ResolutionComboBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCheckBox> VSyncCheckBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UBASelectionBase> FramerateSelection;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UBASelectionBase> ShadingQualitySelection;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UBASelectionBase> GlobalIlluminationQualitySelection;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UBASelectionBase> PostProcessingQualitySelection;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UBASelectionBase> VisualEffectsQualitySelection;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UBASelectionBase> TextureQualitySelection;

	UPROPERTY()
	TArray<FIntPoint> Resolutions;
	
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/BASelectionBase.h"

#include "Components/TextBlock.h"

UBASelectionBase::UBASelectionBase()
{
	CurrentSelection = 0;
	SetIsFocusable(true);
	SetVisibilityInternal(ESlateVisibility::Visible);
}

void UBASelectionBase::NativeConstruct()
{
	if (Options.Num()==0)
	{
		return;
	}

	UpdateCurrentSelection();

	FCustomWidgetNavigationDelegate NavigationDelegate;
	NavigationDelegate.BindDynamic(this, &UBASelectionBase::OnNavigation);
	SetNavigationRuleCustom(EUINavigation::Left, NavigationDelegate);
	SetNavigationRuleCustom(EUINavigation::Right, NavigationDelegate);
}

void UBASelectionBase::Clear()
{
	Options.Reset();
}

void UBASelectionBase::AddOption(const FSelectionOption& InOption)
{
	Options.Add(InOption);
	UpdateCurrentSelection();
}

void UBASelectionBase::SetCurrentSelection(int InIndex)
{
	check(InIndex >= 0 && InIndex < Options.Num());
	CurrentSelection = InIndex;
	UpdateCurrentSelection();
}

void UBASelectionBase::SelectPrevious()
{
	OnNavigation(EUINavigation::Left);
}

void UBASelectionBase::SelectNext()
{
	OnNavigation(EUINavigation::Right);
}

UWidget* UBASelectionBase::OnNavigation(EUINavigation InNavigation)
{
	check(InNavigation == EUINavigation::Left || InNavigation == EUINavigation::Right);

	const auto Direction = InNavigation == EUINavigation::Left ? -1 : 1;

	CurrentSelection+=Direction;
	if (CurrentSelection <0)
	{
		CurrentSelection = Options.Num()-1;
	}
	else if (CurrentSelection >= Options.Num())
	{
		CurrentSelection=0;
	}

	UpdateCurrentSelection();

	OnSelectionChanged.ExecuteIfBound(CurrentSelection);

	return this;
}

void UBASelectionBase::UpdateCurrentSelection()
{
	Label->SetText(Options[CurrentSelection].Label);
}



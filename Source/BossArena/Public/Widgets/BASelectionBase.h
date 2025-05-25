// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/BAWidgetBase.h"
#include "BASelectionBase.generated.h"

class UTextBlock;
/**
 * 
 */

DECLARE_DELEGATE_OneParam(FOnSelectionChangedDelegate, int)

USTRUCT(BlueprintType)
struct FSelectionOption
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Option")
	FText Label;
};

UCLASS()
class BOSSARENA_API UBASelectionBase : public UBAWidgetBase
{
	GENERATED_BODY()

public:
	UBASelectionBase();
	virtual void NativeConstruct() override;

	void Clear();
	void AddOption(const FSelectionOption& InOption);
	void SetCurrentSelection(int InIndex);

	UFUNCTION(BlueprintCallable)
	void SelectPrevious();

	UFUNCTION(BlueprintCallable)
	void SelectNext();

	FOnSelectionChangedDelegate OnSelectionChanged;


protected:
	UFUNCTION()
	UWidget* OnNavigation(EUINavigation InNavigation);

	void UpdateCurrentSelection();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FSelectionOption> Options;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> Label;

	int CurrentSelection;
	
};

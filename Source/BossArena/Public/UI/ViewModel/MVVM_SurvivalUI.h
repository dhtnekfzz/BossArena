// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "Game/BAGameStateBase.h"
#include "MVVM_SurvivalUI.generated.h"

/**
 * 
 */
UCLASS()
class BOSSARENA_API UMVVM_SurvivalUI : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Initialize(ABAGameStateBase* InGameState);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify,Setter, Getter, meta= (AllowPrivateAccess = "true"))
	int32 CurrentWaveCount;

private:
	UFUNCTION()
	void OnGameStateChanged(EBASurvivalGameModeState NewState, const int32 NewWaveCount);

	void SetCurrentWaveCount(int32 Count){ UE_MVVM_SET_PROPERTY_VALUE(CurrentWaveCount, Count); }
	int32 GetCurrentWaveCount() const { return CurrentWaveCount; }
};

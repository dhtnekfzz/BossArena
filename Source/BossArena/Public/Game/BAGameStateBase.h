// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BAGameStateBase.generated.h"

class UMVVM_SurvivalUI;
enum class EBASurvivalGameModeState : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameStateChanged, EBASurvivalGameModeState, NewState, const int32,  NewWaveCount);

//DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGameStateChanged, EBASurvivalGameModeState, const FText&, NewState, NewText)
/**
 * 
 */
UCLASS()
class BOSSARENA_API ABAGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ABAGameStateBase();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	void SetCurrentState(EBASurvivalGameModeState NewState,const int32 NewWaveCount);

	UFUNCTION(BlueprintPure, Category = "Game State")
	FORCEINLINE EBASurvivalGameModeState GetCurrentState() const { return CurrentState; }

	UFUNCTION(BlueprintPure, Category = "Game State")
	FORCEINLINE int32 GetWaveCount() const {return CurrentWaveCount;}

	UPROPERTY(BlueprintAssignable)
	FOnGameStateChanged OnGameStateChanged;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMVVM_SurvivalUI> SurvivalUIViewModelClass;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMVVM_SurvivalUI> SurvivalUIViewModel;

private:
	UPROPERTY(ReplicatedUsing=OnRep_GameStateChanged)
	EBASurvivalGameModeState CurrentState;

	UPROPERTY(ReplicatedUsing = OnRep_GameStateChanged)
	int32 CurrentWaveCount;
	
	UFUNCTION()
	void OnRep_GameStateChanged();
	
};

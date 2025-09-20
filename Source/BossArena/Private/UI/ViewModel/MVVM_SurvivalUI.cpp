// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ViewModel/MVVM_SurvivalUI.h"

#include "Components/SlateWrapperTypes.h"
#include "GameModes/BASurvivalGameMode.h"

void UMVVM_SurvivalUI::Initialize(ABAGameStateBase* InGameState)
{
	if (InGameState)
	{
		InGameState->OnGameStateChanged.AddUniqueDynamic(this, &UMVVM_SurvivalUI::OnGameStateChanged);
		OnGameStateChanged(InGameState->GetCurrentState(), InGameState->GetWaveCount());
	}
}

void UMVVM_SurvivalUI::OnGameStateChanged(EBASurvivalGameModeState NewState, const int32 NewWaveCount)
{
	SetCurrentWaveCount(NewWaveCount);
}

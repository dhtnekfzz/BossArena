// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/BAGameStateBase.h"
#include "UI/ViewModel/MVVM_SurvivalUI.h"

#include "Net/UnrealNetwork.h"


ABAGameStateBase::ABAGameStateBase()
{
}

void ABAGameStateBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SurvivalUIViewModel = NewObject<UMVVM_SurvivalUI>(this, SurvivalUIViewModelClass);

}

void ABAGameStateBase::BeginPlay()
{
	Super::BeginPlay();

}


void ABAGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABAGameStateBase, CurrentState);
	DOREPLIFETIME(ABAGameStateBase, CurrentWaveCount);
}

void ABAGameStateBase::SetCurrentState(EBASurvivalGameModeState NewState, const int32 NewWaveCount)
{ 
	if (!HasAuthority()) return;
	CurrentState = NewState;
	CurrentWaveCount=NewWaveCount;
}

void ABAGameStateBase::OnRep_GameStateChanged()
{
	OnGameStateChanged.Broadcast(CurrentState, CurrentWaveCount);
}

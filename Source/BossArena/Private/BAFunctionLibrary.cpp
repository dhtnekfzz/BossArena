// Fill out your copyright notice in the Description page of Project Settings.


#include "BAFunctionLibrary.h"
#include "GameplayTags.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AssetTypeCategories.h"
#include "BAGameplayTags.h"
#include "GenericTeamAgentInterface.h"
#include "AbilitySystem/BAAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "BATypes/BACountDownAction.h"

UBAAbilitySystemComponent* UBAFunctionLibrary::NativeGetBAASCFromActor(AActor* InActor)
{
	check(InActor);
	
	return CastChecked<UBAAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent((InActor)));
}

void UBAFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UBAAbilitySystemComponent* ASC=NativeGetBAASCFromActor(InActor);

	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

void UBAFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UBAAbilitySystemComponent* ASC=NativeGetBAASCFromActor(InActor);

	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

bool UBAFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UBAAbilitySystemComponent* ASC=NativeGetBAASCFromActor(InActor);
	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UBAFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EBAConfirmType& OutConfirmType)
{
	OutConfirmType=NativeDoesActorHaveTag(InActor, TagToCheck)? EBAConfirmType::Yes : EBAConfirmType::No;
}

UPawnCombatComponent* UBAFunctionLibrary::NativeGetPawnCombatComponent(AActor* InActor)
{
	check(InActor);

	if (IPawnCombatInterface* PawnCombatInterface=Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}

	return nullptr;
}

UPawnCombatComponent* UBAFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor, EBAValidType& OutValidType)
{
	UPawnCombatComponent* CombatComponent=NativeGetPawnCombatComponent(InActor);

	OutValidType=CombatComponent? EBAValidType::Valid : EBAValidType::Invalid;

	return CombatComponent;
}

bool UBAFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);
	
	IGenericTeamAgentInterface* QueryTeamAgent=Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent=Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId()!=TargetTeamAgent->GetGenericTeamId();
	}

	return false;
}

float UBAFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

FGameplayTag UBAFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim,
	float& OutAngleDifference)
{
	check(InAttacker && InVictim);

	const FVector VictimForward=InVictim->GetActorForwardVector();
	const FVector VictimToAttackerNormalized=(InAttacker->GetActorForwardVector()-InVictim->GetActorForwardVector()).GetSafeNormal();

	const float DotResult=FVector::DotProduct(VictimForward, VictimToAttackerNormalized);
	OutAngleDifference=UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult=FVector::CrossProduct(VictimForward,VictimToAttackerNormalized);

	if (CrossResult.Z<0.f)
	{
		OutAngleDifference*=-1.f;
	}

	if (OutAngleDifference>=45.f && OutAngleDifference<=45.f)
	{
		return BAGameplayTags::Shared_Status_HitReact_Front;
	}
	else if (OutAngleDifference<-45.f && OutAngleDifference>=-135.f)
	{
		return BAGameplayTags::Shared_Status_HitReact_Left;
	}
	else if (OutAngleDifference<-135.f || OutAngleDifference>135.f)
	{
		return BAGameplayTags::Shared_Status_HitReact_Back;
	}
	else if (OutAngleDifference>45.f && OutAngleDifference<=135.f)
	{
		return BAGameplayTags::Shared_Status_HitReact_Right;
	}

	return BAGameplayTags::Shared_Status_HitReact_Front;
		
}

bool UBAFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
	check(InAttacker && InDefender);

	const float DotResult=FVector::DotProduct(InAttacker->GetActorForwardVector(), InDefender->GetActorForwardVector());

	return DotResult < -0.1f;
}

bool UBAFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor,
	const FGameplayEffectSpecHandle& InSpecHandle)
{
	UBAAbilitySystemComponent* SourceASC=NativeGetBAASCFromActor(InInstigator);
	UBAAbilitySystemComponent* TargetASC=NativeGetBAASCFromActor(InTargetActor);

	FActiveGameplayEffectHandle ActiveGameplayEffectHandle=SourceASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data,TargetASC);

	return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}

void UBAFunctionLibrary::CountDown(const UObject* WorldContextObject, float TotalTime,
	float UpdateInterval, float& OutRemainingTime, EBACountDownActionInput CountDownInput,
	EBACountDownActionOutput& CountDownOutput, FLatentActionInfo LatentInfo)
{
	UWorld* World=nullptr;

	if (GEngine)
	{
		World=GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::LogAndReturnNull);
	}

	if (!World) return;

	FLatentActionManager& LatentActionManager=World->GetLatentActionManager();

	FBACountDownAction* FoundAction=LatentActionManager.FindExistingAction<FBACountDownAction>(LatentInfo.CallbackTarget,LatentInfo.UUID);

	if (CountDownInput==EBACountDownActionInput::Start)
	{
		if (!FoundAction)
		{
			LatentActionManager.AddNewAction(
				LatentInfo.CallbackTarget,
				LatentInfo.UUID,
				new FBACountDownAction(TotalTime,UpdateInterval,OutRemainingTime,CountDownOutput,LatentInfo)
			);
		}
	}

	if (CountDownInput==EBACountDownActionInput::Cancel)
	{
		if (FoundAction)
		{
			FoundAction->CancelAction();
		}
	}
}



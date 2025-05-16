// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/BAGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "BAFunctionLibrary.h"
#include "BAGameplayTags.h"
#include "AbilitySystem/BAAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"

void UBAGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActivationPolicy==EBAAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UBAGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy==EBAAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UPawnCombatComponent* UBAGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

UBAAbilitySystemComponent* UBAGameplayAbility::GetBAAbilitySystemFromActorInfo() const
{
	return Cast<UBAAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FActiveGameplayEffectHandle UBAGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& InSpecHandle) const
{
	UAbilitySystemComponent* TargetASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	check(TargetASC && InSpecHandle.IsValid());

	return GetBAAbilitySystemFromActorInfo()->ApplyGameplayEffectSpecToTarget(
		*InSpecHandle.Data, TargetASC
	);
}

FActiveGameplayEffectHandle UBAGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& InSpecHandle, EBASuccessfulType& OutSuccessType) 
{
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle=NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHandle);

	OutSuccessType=ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? EBASuccessfulType::Successful : EBASuccessfulType::Failed;

	return ActiveGameplayEffectHandle;
}

void UBAGameplayAbility::ApplyGameplayEffectSpecHandleToHitResults(const FGameplayEffectSpecHandle& InSpecHandle,
	const TArray<FHitResult>& InHitResults)
{
	if (InHitResults.IsEmpty()) return;

	APawn* OwningPawn=CastChecked<APawn>(GetAvatarActorFromActorInfo());

	for (const FHitResult& Hit : InHitResults)
	{
		if (APawn* HitPawn=Cast<APawn>(Hit.GetActor())) 
		{
			if (UBAFunctionLibrary::IsTargetPawnHostile(OwningPawn,HitPawn))
			{
				FActiveGameplayEffectHandle ActiveGameplayEffectHandle=NativeApplyEffectSpecHandleToTarget(HitPawn, InSpecHandle);

				if (ActiveGameplayEffectHandle.WasSuccessfullyApplied())
				{
					FGameplayEventData Data;
					Data.Instigator = OwningPawn;
					Data.Target=HitPawn;

					UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
						HitPawn,
						BAGameplayTags::Shared_Event_HitReact,
						Data
					);
				}
			}
		}
	}
}



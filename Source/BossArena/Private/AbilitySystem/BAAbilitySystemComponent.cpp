// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BAAbilitySystemComponent.h"

#include "BAGameplayTags.h"
#include "BATypes/BAStructTypes.h"

void UBAAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) return;

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;

		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UBAAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	/*
	if (!InInputTag.IsValid() || !InInputTag.MatchesTag(BAGameplayTags::InputTag_MustBeHeld)) return;
	*/

	/*for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag) && AbilitySpec.IsActive())
		{
			CancelAbilityHandle(AbilitySpec.Handle);
		}
	}*/
}

void UBAAbilitySystemComponent::GrantHeroWeaponAbilities(const TArray<FBAHeroAbilitySet>& InDefaultWeaponAbilities,
	int32 ApplyLevel,TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	if (InDefaultWeaponAbilities.IsEmpty()) return;

	for (const FBAHeroAbilitySet& AbilitySet : InDefaultWeaponAbilities)
	{
		if (AbilitySet.IsValid())
		{
			FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
			AbilitySpec.SourceObject=GetAvatarActor();
			AbilitySpec.Level=ApplyLevel;
			AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

			OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec)); 
		}
	}
}



void UBAAbilitySystemComponent::RemovedGrantedHeroWeaponAbilities(
	TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
	if (InSpecHandlesToRemove.IsEmpty()) return;

	for (const FGameplayAbilitySpecHandle& SpecHandle : InSpecHandlesToRemove)
	{
		if(SpecHandle.IsValid())
		{
			ClearAbility(SpecHandle);
		}
	}

	InSpecHandlesToRemove.Empty();
}

bool UBAAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate)
{

	return false;
}

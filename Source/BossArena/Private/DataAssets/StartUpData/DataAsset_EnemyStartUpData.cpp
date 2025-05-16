// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAsset_EnemyStartUpData.h"

#include "AbilitySystem/BAAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/BAEnemyGameplayAbility.h"

void UDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(UBAAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	if (!EnemyCombatAbilities.IsEmpty())
	{
		for (TSubclassOf<UBAEnemyGameplayAbility>& AbilityClass : EnemyCombatAbilities )
		{
			if (!AbilityClass) continue;

			FGameplayAbilitySpec AbilitySpec(AbilityClass,ApplyLevel);
			AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();

			InASCToGive->GiveAbility(AbilitySpec);
			
		}
	}
}

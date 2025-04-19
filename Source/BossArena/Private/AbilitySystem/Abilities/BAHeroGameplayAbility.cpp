// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/BAHeroGameplayAbility.h"

#include "Characters/BAHeroCharacter.h"
#include "Controllers/BAHeroController.h"

ABAHeroCharacter* UBAHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	if (!CachedHeroCharacter.IsValid())
	{
		CachedHeroCharacter=Cast<ABAHeroCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedHeroCharacter.Get();
}

ABAHeroController* UBAHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	if (!CachedHeroController.IsValid())
	{
		CachedHeroController=Cast<ABAHeroController>(CurrentActorInfo->PlayerController);
	}

	return CachedHeroController.Get();
}

UHeroCombatComponent* UBAHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}

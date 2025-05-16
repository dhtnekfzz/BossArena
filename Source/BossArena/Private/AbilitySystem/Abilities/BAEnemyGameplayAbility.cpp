// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/BAEnemyGameplayAbility.h"
#include "AbilitySystem/BAAbilitySystemComponent.h"
#include "BAGameplayTags.h"
#include "Characters/BAEnemyCharacter.h"

ABAEnemyCharacter* UBAEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedBAEnemyCharacter.IsValid())
	{
		CachedBAEnemyCharacter=Cast<ABAEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedBAEnemyCharacter.Get();
}

UEnemyCombatComponent* UBAEnemyGameplayAbility::GetEnemyCombatComponentActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}

FGameplayEffectSpecHandle UBAEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(
	TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle=GetBAAbilitySystemFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = GetBAAbilitySystemFromActorInfo()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		BAGameplayTags::Shared_SetByCaller_BaseDamage,
		InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel())
	);

	return EffectSpecHandle;
}

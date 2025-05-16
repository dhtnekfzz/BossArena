// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/BAGameplayAbility.h"
#include "BAEnemyGameplayAbility.generated.h"

class UEnemyCombatComponent;
class ABAEnemyCharacter;
/**
 * 
 */
UCLASS()
class BOSSARENA_API UBAEnemyGameplayAbility : public UBAGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="BossArena|Ability")
	ABAEnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category="BossArena|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentActorInfo();

	UFUNCTION(BlueprintPure, Category="BossArena|Ability")
	FGameplayEffectSpecHandle MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass,const FScalableFloat& InDamageScalableFloat);

private:
	TWeakObjectPtr<ABAEnemyCharacter> CachedBAEnemyCharacter;
};

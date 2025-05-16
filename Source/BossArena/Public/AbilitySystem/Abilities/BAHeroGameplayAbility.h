// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/BAGameplayAbility.h"
#include "BAHeroGameplayAbility.generated.h"

class UHeroCombatComponent;
class ABAHeroController;
class ABAHeroCharacter;
/**
 * 
 */
UCLASS()
class BOSSARENA_API UBAHeroGameplayAbility : public UBAGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="BossArena|Ability")
	ABAHeroCharacter* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category="BossArena|Ability")
	ABAHeroController* GetHeroControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category="BossArena|Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category="BossArena|Ability")
	FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount);

	UFUNCTION(BlueprintCallable, Category="BossArena|Ability")
	bool GetAbilityRemainingCooldownByTag(FGameplayTag InCooldownTag, float& TotalCooldownTime, float& RemainingCooldownTime);

private:
	TWeakObjectPtr<ABAHeroCharacter> CachedHeroCharacter;
	TWeakObjectPtr<ABAHeroController> CachedHeroController;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BAAbilitySystemComponent.generated.h"

struct FBAHeroSpecialAbilitySet;
struct FBAHeroAbilitySet;
/**
 * 
 */
UCLASS()
class BOSSARENA_API UBAAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);

	UFUNCTION(BlueprintCallable, Category = "BossArena|Ability", meta=(ApplyLevel="1"))
	void GrantHeroWeaponAbilities(const TArray<FBAHeroAbilitySet>& InDefaultWeaponAbilities, const TArray<FBAHeroSpecialAbilitySet>& InSpecialWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);

	UFUNCTION(BlueprintCallable, Category = "BossArena|Ability")
	void RemovedGrantedHeroWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove);

	UFUNCTION(BlueprintCallable, Category = "BossArena|Ability")
	bool TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate);
	
};

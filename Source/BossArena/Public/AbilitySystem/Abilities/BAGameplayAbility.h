// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BAGameplayAbility.generated.h"

class UPawnCombatComponent;
class UBAAbilitySystemComponent;

UENUM(BlueprintType)
enum class EBAAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

/**
 * 
 */
UCLASS()
class BOSSARENA_API UBAGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	//~Begin UGameplayAbility Interface
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~End UGameplayAbility Interface

	UPROPERTY(EditDefaultsOnly, Category = "BossArenaAbility")
	EBAAbilityActivationPolicy AbilityActivationPolicy=EBAAbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintCallable, Category = "BossArena|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "BossArena|Ability")
	UBAAbilitySystemComponent* GetBAAbilitySystemFromActorInfo() const;

	//FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle) const;

	/*UFUNCTION(BlueprintPure, Category = "BossArena|Ability")
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EBA) const;*/
	
	
};

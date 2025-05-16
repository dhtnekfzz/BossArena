// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/BAHeroGameplayAbility.h"
#include "HeroGameplayAbility_PickUpWeapon.generated.h"

class ABAPickUpWeapon;
class ABAWeaponBase;
/**
 * 
 */
UCLASS()
class BOSSARENA_API UHeroGameplayAbility_PickUpWeapon : public UBAHeroGameplayAbility
{
	GENERATED_BODY()

protected:
	//~Begin UGameplayAbility Interface
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~End UGameplayAbility Interface

	UFUNCTION(BlueprintCallable)
	void FindWeapon();

	UFUNCTION(BlueprintCallable)
	void PickUpWeapon();


private:
	UPROPERTY(EditDefaultsOnly)
	float BoxTraceDistance=50.f;

	UPROPERTY(EditDefaultsOnly)
	FVector TraceBoxSize=FVector(100.f);

	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> WeaponTraceChannel;

	UPROPERTY(EditDefaultsOnly)
	bool bDrawDebugShape=false;

	UPROPERTY()
	TObjectPtr<ABAPickUpWeapon> Weapon;
	
};

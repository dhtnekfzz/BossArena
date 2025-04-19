// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "AbilitySystem/Abilities/BAGameplayAbility.h"
#include "BAStructTypes.generated.h"

class UInputMappingContext;
class UBAHeroLinkedAnimLayer;
class UBAGameplayAbility;

USTRUCT(BlueprintType)
struct FBAInputActionConfig
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(Category="Input"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputAction;

	bool IsValid() const { return InputTag.IsValid()&&InputAction; }
};


USTRUCT(BlueprintType)
struct FBAHeroAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Category="Input"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UBAGameplayAbility> AbilityToGrant;

	bool IsValid() const { return InputTag.IsValid()&&AbilityToGrant;}
};

USTRUCT(BlueprintType)
struct FBAHeroWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UBAHeroLinkedAnimLayer> WeaponAnimLayerToLink;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContest;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty="InputTag"))
	TArray<FBAHeroAbilitySet> DefaultWeaponAbilities;
};

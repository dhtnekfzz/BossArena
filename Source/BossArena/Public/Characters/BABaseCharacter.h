// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BABaseCharacter.generated.h"

class UDataAsset_StartUpDataBase;
class UBAAttributeSet;
class UBAAbilitySystemComponent;

UCLASS()
class BOSSARENA_API ABABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABABaseCharacter();

	//~ Begin InAbilitySystemInterface Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End InAbilitySystemInterface Interface

protected:
	//~ Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UBAAbilitySystemComponent* BAAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UBAAttributeSet* BAAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpData;

public:
	FORCEINLINE UBAAbilitySystemComponent* GetBAAbilitySystemComponent() const { return BAAbilitySystemComponent; }
	FORCEINLINE UBAAttributeSet* GetBAAttributeSet() const { return BAAttributeSet; }
	

};

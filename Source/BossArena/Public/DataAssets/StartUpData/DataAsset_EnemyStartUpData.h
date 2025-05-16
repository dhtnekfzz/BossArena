// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "DataAsset_EnemyStartUpData.generated.h"

class UBAEnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class BOSSARENA_API UDataAsset_EnemyStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UBAAbilitySystemComponent* InASCToGive, int32 ApplyLeve = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="StartUpData")
	TArray<TSubclassOf<UBAEnemyGameplayAbility>> EnemyCombatAbilities;
	
};

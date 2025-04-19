// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "DataAsset_HeroStartUpData.generated.h"

struct FBAHeroAbilitySet;
/**
 * 
 */
UCLASS()
class BOSSARENA_API UDataAsset_HeroStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UBAAbilitySystemComponent* InASCToGive, int32 ApplyLeve = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta=(TitleProperty="InputTag"))
	TArray<FBAHeroAbilitySet> HeroStartUpAbilitySets;
	
};

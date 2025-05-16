// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_HeroStartUpData.h"
#include "DataAsset_WeaponPickUpData.generated.h"

/**
 * 
 */
UCLASS()
class BOSSARENA_API UDataAsset_WeaponPickUpData : public UDataAsset_HeroStartUpData
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickup|Mesh")
	TObjectPtr<UStaticMesh> DisplayMesh;

	TArray<UDataAsset_HeroStartUpData> DisplayMeshNames;

	
};

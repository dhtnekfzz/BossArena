// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/BABaseAnimInstance.h"
#include "BAHeroLinkedAnimLayer.generated.h"

class UBAHeroAnimInstance;
/**
 * 
 */
UCLASS()
class BOSSARENA_API UBAHeroLinkedAnimLayer : public UBABaseAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta=(NotBlueprintThreadSafe))
	UBAHeroAnimInstance* GetHeroAnimInstance() const;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "BAHeroController.generated.h"

/**
 * 
 */
UCLASS()
class BOSSARENA_API ABAHeroController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	ABAHeroController();
	
	//~Begin IGenericTeamAgentInterface Interface
	virtual FGenericTeamId GetGenericTeamId() const override;
	//~End IGenericTeamAgentInterface Interface

private:
	FGenericTeamId HeroTeamID;
};

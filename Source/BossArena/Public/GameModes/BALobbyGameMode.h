// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/BAGameModeBase.h"
#include "BALobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BOSSARENA_API ABALobbyGameMode : public ABAGameModeBase
{
	GENERATED_BODY()

public:

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;

private:

	void StartGame();

	uint32 NumberOfPlayers = 0;

	FTimerHandle GameStartTimer;
	
};

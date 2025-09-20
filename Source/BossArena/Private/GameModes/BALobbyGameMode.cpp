// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BALobbyGameMode.h"

#include "Game/BASessionSubSystem.h"

void ABALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	++NumberOfPlayers;
	
	if (NumberOfPlayers >=2)
	{
		StartGame();
	}
}

void ABALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	--NumberOfPlayers;
	
}

void ABALobbyGameMode::StartGame()
{
	
	auto GameInstance= GetGameInstance();
	
	if (GameInstance==nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not GameInstance"));
	}

	UBASessionSubSystem* SessionSubSystem= GameInstance->GetSubsystem<UBASessionSubSystem>();

	if (SessionSubSystem==nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not GameInstance"));
		return;
	}
	
	SessionSubSystem->StartSession();

	UWorld* World = GetWorld();
	if (!ensure(World!=nullptr)) return;

	

	bUseSeamlessTravel = true;
	World->ServerTravel("/Game/BossArena/Maps/L_test?listen");
}

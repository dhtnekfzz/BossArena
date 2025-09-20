// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/BASessionSubSystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSubSystem.h"
#include "Online/OnlineSessionNames.h"
#include "OnlineSessionSettings.h"
#include "Engine/Engine.h"

const static FName SESSION_NAME = TEXT("Game");
const static FName SERVER_NAME_SETTINGS_KEY = TEXT("ServerName");

void UBASessionSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get(); 
	if (!Subsystem) return;
	SessionInterface = Subsystem->GetSessionInterface();
	if (!SessionInterface) return;

	SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UBASessionSubSystem::OnCreateSessionComplete);
	SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UBASessionSubSystem::OnFindSessionsComplete);
	SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UBASessionSubSystem::OnJoinSessionComplete);

}

void UBASessionSubSystem::HostSession(FString ServerName)
{
	DesiredServerName = ServerName;
	if (!SessionInterface.IsValid()) return;

	auto ExistingSession=SessionInterface->GetNamedSession(SESSION_NAME);

	if (ExistingSession!=nullptr)
	{
		SessionInterface->DestroySession(SESSION_NAME);
	}
	else
	{
		CreateSession();
	}
}

void UBASessionSubSystem::FindSessions()
{
	if (!SessionInterface.IsValid()) return;
	
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->MaxSearchResults = 100;
	SessionSearch->bIsLanQuery=true;
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE,true, EOnlineComparisonOp::Equals);
	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	
}

void UBASessionSubSystem::JoinSession(int32 SessionIndex)
{
	if (!SessionInterface.IsValid()) return;
	if (!SessionSearch.IsValid()) return;

	SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[SessionIndex]);
}

void UBASessionSubSystem::StartSession()
{
	if (!SessionInterface.IsValid()) return;

	SessionInterface->StartSession(SESSION_NAME);
}


void UBASessionSubSystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Session created successfully: %s"), *SessionName.ToString());
		
		GetWorld()->ServerTravel(TEXT("/Game/BossArena/Maps/L_Lobby?listen"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create session!"));
	}

}

void UBASessionSubSystem::OnFindSessionsComplete(bool bWasSuccessful)
{
	if (bWasSuccessful && SessionSearch.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Found %d sessions."), SessionSearch->SearchResults.Num());
		TArray<FBPSessionResult> BlueprintResults;

		int i=0;
		for (const FOnlineSessionSearchResult& Result : SessionSearch->SearchResults)
		{
			FBPSessionResult BPResult;
			BPResult.MaxPlayers = Result.Session.SessionSettings.NumPublicConnections;
			BPResult.CurrentPlayers = BPResult.MaxPlayers - Result.Session.NumOpenPublicConnections;
			BPResult.ServerIndex=i;
			++i;

			FString ServerName;
			if (Result.Session.SessionSettings.Get(SERVER_NAME_SETTINGS_KEY, ServerName))
			{
				BPResult.ServerName=ServerName;
			}
			else
			{
				BPResult.ServerName="Could not find name";
			}
			
			BlueprintResults.Add(BPResult);
		}
		OnSessionsFound.Broadcast(BlueprintResults);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find sessions."));
		OnSessionsFound.Broadcast(TArray<FBPSessionResult>());
	}
}

void UBASessionSubSystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (Result != EOnJoinSessionCompleteResult::Success) return;
	if (!SessionInterface.IsValid()) return;

	UE_LOG(LogTemp, Warning, TEXT("Joined session successfully: %s"),*SessionName.ToString());
		
	FString Address = "";
	if (!SessionInterface->GetResolvedConnectString(SessionName, Address))
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not connect string."));
		return;
	}
	
	APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
	if (!ensure(PlayerController!=nullptr)) return;
	
	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);

}

void UBASessionSubSystem::OnDestroySessionComplete(FName SessionName, bool Success)
{
	if (Success)
		CreateSession();
}

void UBASessionSubSystem::CreateSession()
{
	if (!SessionInterface.IsValid()) return;

	FOnlineSessionSettings SessionSettings;
	
	SessionSettings.NumPublicConnections = 5; 
	SessionSettings.bShouldAdvertise = true;      
	SessionSettings.bIsLANMatch = true;          
	SessionSettings.bUsesPresence = true;
	SessionSettings.Set(SERVER_NAME_SETTINGS_KEY, DesiredServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	
	SessionInterface->CreateSession(0,SESSION_NAME, SessionSettings);
}

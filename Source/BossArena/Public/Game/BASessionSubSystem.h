// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "BASessionSubSystem.generated.h"

USTRUCT(BlueprintType)
struct FBPSessionResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Session")
	FString ServerName;

	UPROPERTY(BlueprintReadOnly, Category = "Session")
	int32 CurrentPlayers;

	UPROPERTY(BlueprintReadOnly, Category = "Session")
	int32 MaxPlayers;

	UPROPERTY(BlueprintReadOnly, Category = "Session")
	int32 ServerIndex;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSessionsFoundDelegate, const TArray<FBPSessionResult>&, SessionResults);


/**
 * 
 */
UCLASS()
class BOSSARENA_API UBASessionSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UPROPERTY(BlueprintAssignable, Category = "Sessions")
	FOnSessionsFoundDelegate OnSessionsFound;

	UFUNCTION(BlueprintCallable, Category = "Sessions")
	void HostSession(FString ServerName);

	UFUNCTION(BlueprintCallable, Category = "Sessions")
	void FindSessions();
	
	UFUNCTION(BlueprintCallable, Category = "Sessions")
	void JoinSession(int32 SessionIndex);

	void StartSession();
	
protected:
	
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	UFUNCTION(BlueprintCallable, Category = "Sessions")
	void OnFindSessionsComplete(bool bWasSuccessful);
	
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnDestroySessionComplete(FName SessionName, bool Success);

private:
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	
	FString DesiredServerName;
	void CreateSession();
	
};

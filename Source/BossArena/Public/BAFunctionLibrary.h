// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BAFunctionLibrary.generated.h"

class UBAAbilitySystemComponent;
struct FGameplayTag;

UENUM()
enum class EBAConfirmType : uint8
{
	Yes,
	No
};
/**
 * 
 */
UCLASS()
class BOSSARENA_API UBAFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UBAAbilitySystemComponent* NativeGetBAASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "BossArena|FuntionLibarary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "BossArena|FuntionLibarary")
	static void RemoveGameplayFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = "BossArena|FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs="OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor,FGameplayTag TagToCheck, EBAConfirmType& OutConfirmType);
	
};

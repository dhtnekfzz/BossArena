// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BATypes/BAEnumTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BAFunctionLibrary.generated.h"

struct FScalableFloat;
struct FGameplayEffectSpecHandle;
class UPawnCombatComponent;
class UBAAbilitySystemComponent;
struct FGameplayTag;

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
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = "BossArena|FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs="OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor,FGameplayTag TagToCheck, EBAConfirmType& OutConfirmType);

	static UPawnCombatComponent* NativeGetPawnCombatComponent(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "BossArena|FunctionLibrary", meta = (DisplayName = "Get Pawn Combat Component From Actor", ExpandEnumAsExecs="OutValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, EBAValidType& OutValidType);

	UFUNCTION(BlueprintCallable, Category = "BossArena|FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintPure, Category = "BossArena|FunctionLibrary", meta = (CompactNodeTitle="Get Value At Level"))
	static float GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat,float InLevel);

	UFUNCTION(BlueprintPure, Category = "BossArena|FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference);

	UFUNCTION(BlueprintPure, Category = "BossArena|FunctionLibrary")
	static bool IsValidBlock(AActor* InAttacker, AActor* InDefender);

	UFUNCTION(BlueprintCallable, Category = "BossArena|FunctionLibrary")
	static bool ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "BossArena|FunctionLibrary",meta=(Latent, WorldContext = "WorldContextObject",LatentInfo="LatentInfo",ExpandEnumAsExecs="CountDownInput|CountDownOutput",TotalTime="1.0", UpdateInterval="0.1"))
	static void CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval, float& OutRemainingTime, EBACountDownActionInput CountDownInput,
	UPARAM(DisplayName="Output") EBACountDownActionOutput& CountDownOutput, FLatentActionInfo LatentInfo);
	
}; 

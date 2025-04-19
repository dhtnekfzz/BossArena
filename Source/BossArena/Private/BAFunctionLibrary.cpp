// Fill out your copyright notice in the Description page of Project Settings.


#include "BAFunctionLibrary.h"
#include "GameplayTags.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/BAAbilitySystemComponent.h"

UBAAbilitySystemComponent* UBAFunctionLibrary::NativeGetBAASCFromActor(AActor* InActor)
{
	check(InActor);

	return CastChecked<UBAAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent((InActor)));
}

void UBAFunctionLibrary::RemoveGameplayFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UBAAbilitySystemComponent* ASC=NativeGetBAASCFromActor(InActor);

	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

void UBAFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UBAAbilitySystemComponent* ASC=NativeGetBAASCFromActor(InActor);

	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

bool UBAFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UBAAbilitySystemComponent* ASC=NativeGetBAASCFromActor(InActor);
	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UBAFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EBAConfirmType& OutConfirmType)
{
	OutConfirmType=NativeDoesActorHaveTag(InActor, TagToCheck)? EBAConfirmType::Yes : EBAConfirmType::No;
}



// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/BABaseAnimInstance.h"

#include "BAFunctionLibrary.h"

bool UBABaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn=TryGetPawnOwner())
	{
		return UBAFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}

	return true;
}

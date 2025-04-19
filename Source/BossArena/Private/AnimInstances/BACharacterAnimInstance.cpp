// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/BACharacterAnimInstance.h"

#include "Characters/BABaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBACharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter=Cast<ABABaseCharacter>(TryGetPawnOwner());

	if (OwningCharacter)
	{
		OwningMovementComponent=OwningCharacter->GetCharacterMovement();
	}
}

void UBACharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter||!OwningMovementComponent)
	{
		return;
	}

	GroundSpeed=OwningCharacter->GetVelocity().Size2D();

	bHasAcceleration=OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D()>0.f;
}

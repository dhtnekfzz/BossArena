// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Hero/BAHeroAnimInstance.h"

#include "Characters/BAHeroCharacter.h"

void UBAHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningHeroCharacter=Cast<ABAHeroCharacter>(OwningCharacter);
	}
}

void UBAHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (bHasAcceleration)
	{
		IdleElpasedTime=0.f;
		bShouldEnterRelaxState=false;
	}
	else
	{
		IdleElpasedTime+=DeltaSeconds;
		bShouldEnterRelaxState=IdleElpasedTime>=EnterRelaxStateThreshold;
	}
		
}

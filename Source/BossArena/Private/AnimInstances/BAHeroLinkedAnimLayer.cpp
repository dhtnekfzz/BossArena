// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/BAHeroLinkedAnimLayer.h"

#include "AnimInstances/Hero/BAHeroAnimInstance.h"

UBAHeroAnimInstance* UBAHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
	return Cast<UBAHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}

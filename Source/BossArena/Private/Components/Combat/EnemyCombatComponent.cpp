// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "BAFunctionLibrary.h"
#include "BAGameplayTags.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Characters/BAEnemyCharacter.h"
#include "Components/BoxComponent.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor)) return;

	OverlappedActors.AddUnique(HitActor);

	bool bIsValidBlock=false;
	
	const bool bIsPlayerBlocking=UBAFunctionLibrary::NativeDoesActorHaveTag(HitActor,BAGameplayTags::Player_Status_Blocking);
	const bool bIsMyAttackUnblockable=UBAFunctionLibrary::NativeDoesActorHaveTag(GetOwningPawn(), BAGameplayTags::Enemy_Status_Unblockable);

	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		bIsValidBlock=UBAFunctionLibrary::IsValidBlock(GetOwningPawn(),HitActor);
	}

	FGameplayEventData EventData;
	EventData.Instigator=GetOwningPawn();
	EventData.Target=HitActor;

	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitActor,
			BAGameplayTags::Player_Event_SuccessfulBlock,
			EventData
		);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			BAGameplayTags::Shared_Event_MeleeHit,
			EventData
		);
	}
}

void UEnemyCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
}

void UEnemyCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	ABAEnemyCharacter* OwningEnemyCharacter=GetOwningPawn<ABAEnemyCharacter>();

	check(OwningEnemyCharacter);

	UBoxComponent* RightHandCollisionBox=OwningEnemyCharacter->GetRightHandCollisionBox();
	UBoxComponent* LeftHandCollisionBox=OwningEnemyCharacter->GetLeftHandCollisionBox();

	check(RightHandCollisionBox && LeftHandCollisionBox);

	switch (ToggleDamageType)
	{
	case EToggleDamageType::RightHand:
		RightHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	case EToggleDamageType::LeftHand:
		LeftHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
	default:
		break;
	}

	if (!bShouldEnable)
	{
		OverlappedActors.Empty();
	}
}


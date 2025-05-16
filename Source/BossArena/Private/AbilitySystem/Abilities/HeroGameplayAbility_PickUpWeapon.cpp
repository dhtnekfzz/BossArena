// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/HeroGameplayAbility_PickUpWeapon.h"

#include "Characters/BAHeroCharacter.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "Items/PickUps/BAPickUpWeapon.h"
#include "Items/Weapons/BAHeroWeapon.h"
#include "Items/Weapons/BAWeaponBase.h"
#include "Kismet/KismetSystemLibrary.h"

void UHeroGameplayAbility_PickUpWeapon::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo,
                                                      const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
}

void UHeroGameplayAbility_PickUpWeapon::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UHeroGameplayAbility_PickUpWeapon::FindWeapon()
{
	Weapon=nullptr;
	TArray<FHitResult> TraceHits;
	
	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetHeroCharacterFromActorInfo(),
		GetHeroCharacterFromActorInfo()->GetActorLocation(),
		GetHeroCharacterFromActorInfo()->GetActorLocation() + -GetHeroCharacterFromActorInfo()->GetActorUpVector()*BoxTraceDistance,
		TraceBoxSize/2.f,
		(-GetHeroCharacterFromActorInfo()->GetActorUpVector()).ToOrientationRotator(),
		WeaponTraceChannel,
		false,
		TArray<AActor*>(),
		bDrawDebugShape?EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		TraceHits,
		true
	);

	for (const FHitResult& TraceHit : TraceHits)
	{
		if (ABAPickUpWeapon* FoundWeapon = Cast<ABAPickUpWeapon>(TraceHit.GetActor()))
		{
			Weapon=FoundWeapon;
		}
	}
	
	if (!Weapon)
	{
		CancelAbility(GetCurrentAbilitySpecHandle(),GetCurrentActorInfo(),GetCurrentActivationInfo(),true);
	}
}

void UHeroGameplayAbility_PickUpWeapon::PickUpWeapon()
{
	if (!Weapon)
	{
		CancelAbility(GetCurrentAbilitySpecHandle(),GetCurrentActorInfo(),GetCurrentActivationInfo(),true);
		return;
	}

	Weapon->PickUp(GetBAAbilitySystemFromActorInfo());

	TMap<FGameplayTag, ABAWeaponBase*> CarriedWeaponMap=GetHeroCombatComponentFromActorInfo()->GetCharacterCarriedWeaponMap();


	
	;
}

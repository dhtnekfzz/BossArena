// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BABaseCharacter.h"
#include "AbilitySystem/BAAbilitySystemComponent.h"
#include "AbilitySystem/BAAttributeSet.h"
#include "MotionWarpingComponent.h"

// Sets default values
ABABaseCharacter::ABABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	bReplicates=true;

	GetMesh()->bReceivesDecals=false;

	BAAbilitySystemComponent=CreateDefaultSubobject<UBAAbilitySystemComponent>(TEXT("BAAbilitySystemComponent"));
	BAAbilitySystemComponent->SetIsReplicated(true);
	BAAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);

	BAAttributeSet=CreateDefaultSubobject<UBAAttributeSet>(TEXT("BAAttributeSet"));

	MotionWarpingComponent=CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
	
}

UAbilitySystemComponent* ABABaseCharacter::GetAbilitySystemComponent() const
{
	return GetBAAbilitySystemComponent();
}

UPawnCombatComponent* ABABaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

UPawnUIComponent* ABABaseCharacter::GetPawnUIComponent() const
{
	return nullptr;
}

void ABABaseCharacter::Multicast_PlayDeathEffects_Implementation(UObject* NiagaraSystem)
{
	BP_PlayDeathEffects(NiagaraSystem);
}

void ABABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (BAAbilitySystemComponent)
	{
		BAAbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}


// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/PickUps/BAPickUpWeapon.h"
#include "Items/Weapons/BAHeroWeapon.h"
#include "DataAssets/StartUpData/DataAsset_HeroStartUpData.h"
#include "BAGameplayTags.h"
#include "AbilitySystem/Abilities/BAGameplayAbility.h"
#include "AbilitySystem/BAAbilitySystemComponent.h"
#include "BATypes/BAStructTypes.h"
#include "Characters/BAHeroCharacter.h"
#include "Components/Combat/HeroCombatComponent.h"

ABAPickUpWeapon::ABAPickUpWeapon()
{
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
}

void ABAPickUpWeapon::PickUp(UBAAbilitySystemComponent* AbilitySystemComponent)
{
	if (!WeaponData) return;
	
	ABAHeroCharacter* HeroCharacter=Cast<ABAHeroCharacter>(AbilitySystemComponent->GetAvatarActor());
	TMap<FGameplayTag, ABAWeaponBase*>& CarriedWeaponMap=HeroCharacter->GetHeroCombatComponent()->GetCharacterCarriedWeaponMap();
	
	if (WeaponData)
	{
		static const FString ContextString(TEXT("Weapon PickUp"));
		FWeaponData* Row=WeaponData->FindRow<FWeaponData>(WeaponName,ContextString,true);
		if (Row&&Row->WeaponAbilityData)
		{
			Row->WeaponAbilityData->GiveToAbilitySystemComponent(AbilitySystemComponent);
		}
	}
	
	if (!CarriedWeaponMap.IsEmpty())
	{
		FGameplayTag GameplayTag;
		if (WeaponData)
		{
			for (auto CarriedWeapon : CarriedWeaponMap)
			{
				FName RowNameFromTag=CarriedWeapon.Key.GetTagName();
				WeaponName=RowNameFromTag;
				
				static const FString ContextString(TEXT("Carried Weapon"));
				FWeaponData* Row=WeaponData->FindRow<FWeaponData>(WeaponName,ContextString,true);
				if (Row&&Row->WeaponMesh)
				{
					WeaponMesh->SetStaticMesh(Row->WeaponMesh);
					GameplayTag=CarriedWeapon.Key;
				}
				CarriedWeapon.Value->Destroy();
			}
			WeaponName=GameplayTag.GetTagName();
			CarriedWeaponMap.Empty();
		}
		TArray<FGameplayAbilitySpec*> FoundAbilitySpecs;
		AbilitySystemComponent->GetActivatableGameplayAbilitySpecsByAllMatchingTags(GameplayTag.GetSingleTagContainer(), FoundAbilitySpecs);

		if (!FoundAbilitySpecs.IsEmpty())
		{
			for (FGameplayAbilitySpec* SpecToRemove : FoundAbilitySpecs)
			{
				AbilitySystemComponent->ClearAbility(SpecToRemove->Handle);
			}
		}
	}

	BP_OnWeaponPickUp();
}

void ABAPickUpWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (UDataTable* LoadedData=WeaponData)
	{
		static const FString ContextString(TEXT("Weapon Mesh"));
		FWeaponData* Row=LoadedData->FindRow<FWeaponData>(WeaponName,ContextString,true);
		if (Row&&Row->WeaponMesh)
		{
			WeaponMesh->SetStaticMesh(Row->WeaponMesh);
		}	
	}
	
}

void ABAPickUpWeapon::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABAHeroCharacter* OverlappedHeroCharacter=Cast<ABAHeroCharacter>(OtherActor))
	{
		OverlappedHeroCharacter->GetBAAbilitySystemComponent()->TryActivateAbilityByTag(BAGameplayTags::Player_Ability_PickUp_Weapon);
	}
}



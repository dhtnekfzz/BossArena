


#include "Components/Combat/PawnCombatComponent.h"

#include "AnimInstances/BAHeroLinkedAnimLayer.h"
#include "Characters/BAHeroCharacter.h"
#include "Components/BoxComponent.h"
#include "Items/Weapons/BAWeaponBase.h"
#include "Net/UnrealNetwork.h"


UPawnCombatComponent::UPawnCombatComponent()
{
	//SetIsReplicated(true);
	SetIsReplicatedByDefault(true);
}

void UPawnCombatComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPawnCombatComponent, CharacterCarriedWeapons);
	
}

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, ABAWeaponBase* InWeaponToRegister,bool bMainWeapon, bool bRegisterAsEquippedWeapon)
{

	if (!GetOwner()->HasAuthority()) return;
	
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("A named named %s has already been added as carried weapon"), *InWeaponTagToRegister.ToString());

	if (!bMainWeapon) return;
	
	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

	InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &UPawnCombatComponent::OnHitTargetActor);
	InWeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this, &UPawnCombatComponent::OnWeaponPulledFromTargetActor);

	FCarriedWeaponEntry NewEntry;
	NewEntry.WeaponTag = InWeaponTagToRegister;
	NewEntry.WeaponInstance = InWeaponToRegister;
	CharacterCarriedWeapons.Add(NewEntry);

	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag=InWeaponTagToRegister;
	}

	
}

void UPawnCombatComponent::OnRep_CurrentEquippedWeaponTag()
{
	Multicast_UpdateWeaponVisuals(CurrentEquippedWeaponTag);
}


ABAWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{

	const FCarriedWeaponEntry* FoundEntry = CharacterCarriedWeapons.FindByPredicate(
		[&InWeaponTagToGet](const FCarriedWeaponEntry& Entry)
		{
			return Entry.WeaponTag == InWeaponTagToGet;
		}
	);

	
	return FoundEntry ? FoundEntry->WeaponInstance : nullptr;
}

ABAWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid()) return nullptr;

	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

TMap<FGameplayTag, ABAWeaponBase*>& UPawnCombatComponent::GetCharacterCarriedWeaponMap()
{
	return CharacterCarriedWeaponMap;
}

TArray<FCarriedWeaponEntry>& UPawnCombatComponent::GetCharacterCarriedWeaponEntry()
{
	return CharacterCarriedWeapons;
}

void UPawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	if (!GetOwner()->HasAuthority()) return;
	
	if (ToggleDamageType==EToggleDamageType::CurrentEquippedWeapon)
	{
		ToggleCurrentEquippedWeaponCollision(bShouldEnable);
	}
	else
	{
		ToggleBodyCollisionBoxCollision(bShouldEnable, ToggleDamageType);
	}
}

void UPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	
}

void UPawnCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	
}

void UPawnCombatComponent::ToggleCurrentEquippedWeaponCollision(bool bShouldEnable)
{
	ABAWeaponBase* WeaponToToggle=GetCharacterCurrentEquippedWeapon();
	check(WeaponToToggle)
	if (bShouldEnable)
	{
		WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		OverlappedActors.Empty();
	}
}

void UPawnCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnable,
	EToggleDamageType ToggleDamageType)
{
}



void UPawnCombatComponent::Multicast_UpdateWeaponVisuals_Implementation(FGameplayTag InCurrentEquipWeaponTag)
{
}






#include "Components/Combat/HeroCombatComponent.h"

#include "Items/Weapons/BAHeroWeapon.h"


ABAHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<ABAHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

ABAHeroWeapon* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
	return Cast<ABAHeroWeapon>(GetCharacterCurrentEquippedWeapon());
}

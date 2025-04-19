#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/PawnExtensionComponent.h"
#include "PawnCombatComponent.generated.h"


class ABAWeaponBase;

UCLASS()
class BOSSARENA_API UPawnCombatComponent : public UPawnExtensionComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "BossArena|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, ABAWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon=false);
	
	UPROPERTY(BlueprintReadWrite, Category = "BossArena|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION(BlueprintCallable, Category = "BossArena|Combat")
	ABAWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UFUNCTION(BlueprintCallable, Category = "BossArena|Combat")
	ABAWeaponBase* GetCharacterCurrentEquippedWeapon() const;

	
private:
	TMap<FGameplayTag, ABAWeaponBase*> CharacterCarriedWeaponMap;
	

};



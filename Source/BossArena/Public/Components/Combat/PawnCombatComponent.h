#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "BATypes/BAEnumTypes.h"
#include "Components/PawnExtensionComponent.h"
#include "PawnCombatComponent.generated.h"


class ABAWeaponBase;

UCLASS()
class BOSSARENA_API UPawnCombatComponent : public UPawnExtensionComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "BossArena|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, ABAWeaponBase* InWeaponToRegister,bool bMainWeapon, bool bRegisterAsEquippedWeapon=false);
	
	UPROPERTY(BlueprintReadWrite, Category = "BossArena|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION(BlueprintCallable, Category = "BossArena|Combat")
	ABAWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UFUNCTION(BlueprintCallable, Category = "BossArena|Combat")
	ABAWeaponBase* GetCharacterCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "BossArena|Combat")
	TMap<FGameplayTag, ABAWeaponBase*>& GetCharacterCarriedWeaponMap();

	UFUNCTION(BlueprintCallable, Category = "BossArena|Combat")
	void ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType =EToggleDamageType::CurrentEquippedWeapon);

	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);

protected:
	virtual void ToggleCurrentEquippedWeaponCollision(bool bShouldEnable);
	virtual void ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType);
	
	TArray<AActor*> OverlappedActors;
	
private:
	TMap<FGameplayTag, ABAWeaponBase*> CharacterCarriedWeaponMap;
	
	

};




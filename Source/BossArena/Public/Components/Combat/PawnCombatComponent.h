#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "BATypes/BAEnumTypes.h"
#include "Components/PawnExtensionComponent.h"
#include "PawnCombatComponent.generated.h"


class ABAWeaponBase;

USTRUCT(BlueprintType)
struct FCarriedWeaponEntry
{
	GENERATED_BODY()
	// 어떤 무기인지 식별하는 태그
	UPROPERTY()
	FGameplayTag WeaponTag;

	// 실제 무기 액터에 대한 포인터
	UPROPERTY()
	TObjectPtr<ABAWeaponBase> WeaponInstance;

	// 기본 생성자
	FCarriedWeaponEntry() : WeaponTag(FGameplayTag()), WeaponInstance(nullptr) {}

	// 배열에서 특정 태그를 가진 요소를 쉽게 찾기 위해 비교 연산자를 오버로딩합니다.
	bool operator==(const FGameplayTag& OtherTag) const
	{
		return WeaponTag == OtherTag;
	}
};

UCLASS()
class BOSSARENA_API UPawnCombatComponent : public UPawnExtensionComponent
{
	GENERATED_BODY()

public:
	UPawnCombatComponent();
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(BlueprintCallable, Category = "BossArena|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, ABAWeaponBase* InWeaponToRegister,bool bMainWeapon, bool bRegisterAsEquippedWeapon=false);
	
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing=OnRep_CurrentEquippedWeaponTag, Category = "BossArena|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION()
	void OnRep_CurrentEquippedWeaponTag();

	UFUNCTION(BlueprintCallable, Category = "BossArena|Combat")
	ABAWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UFUNCTION(BlueprintCallable, Category = "BossArena|Combat")
	ABAWeaponBase* GetCharacterCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "BossArena|Combat")
	TMap<FGameplayTag, ABAWeaponBase*>& GetCharacterCarriedWeaponMap();
	
	UFUNCTION(BlueprintCallable, Category = "BossArena|Combat")
	TArray<FCarriedWeaponEntry>& GetCharacterCarriedWeaponEntry();

	UFUNCTION(BlueprintCallable, Category = "BossArena|Combat")
	void ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType =EToggleDamageType::CurrentEquippedWeapon);

	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);


protected:
	virtual void ToggleCurrentEquippedWeaponCollision(bool bShouldEnable);
	virtual void ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType);
	
	TArray<AActor*> OverlappedActors;

	UFUNCTION(NetMulticast, Reliable, Category = "BossArena|Combat")
	void Multicast_UpdateWeaponVisuals(FGameplayTag InCurrentEquipWeaponTag);


private:
	UPROPERTY()
	TMap<FGameplayTag, ABAWeaponBase*> CharacterCarriedWeaponMap;

	UPROPERTY(Replicated)
	TArray<FCarriedWeaponEntry> CharacterCarriedWeapons;
	

};




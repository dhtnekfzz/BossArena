// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUps/BAPickUpBase.h"
#include "BAPickUpWeapon.generated.h"

class UDataAsset_HeroStartUpData;
class ABAHeroCharacter;
class UBAAbilitySystemComponent;
class UBAGameplayAbility;
/**
 * 
 */
UCLASS()
class BOSSARENA_API ABAPickUpWeapon : public ABAPickUpBase
{
	GENERATED_BODY()

public:
	ABAPickUpWeapon();
	
	void PickUp(UBAAbilitySystemComponent* AbilitySystemComponent);
	
	UPROPERTY(BlueprintReadWrite, Category = "WeaponMesh")
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

protected:
	virtual void BeginPlay() override;
	
	virtual void OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WeaponData")
	TObjectPtr<UDataTable> WeaponData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponData")
	FName WeaponName; 
	
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="On Weapon PickUp"))
	void BP_OnWeaponPickUp();
};

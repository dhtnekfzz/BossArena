// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/BAWeaponBase.h"

#include "Components/BoxComponent.h"

// Sets default values
ABAWeaponBase::ABAWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh=CreateDefaultSubobject<UStaticMeshComponent>(FName("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	WeaponCollisionBox=CreateDefaultSubobject<UBoxComponent>(FName("WeaponCollisionBox"));
	WeaponCollisionBox->SetupAttachment(GetRootComponent());
	WeaponCollisionBox->SetBoxExtent(FVector(20.f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	

}




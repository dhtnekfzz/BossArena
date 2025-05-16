// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BAHeroCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "BAGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/BAAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "Components/Input/BAInputComponent.h"
#include "Components/UI/HeroUIComponent.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ABAHeroCharacter::ABAHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	SpringArm=CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength=200.f;
	SpringArm->SocketOffset=FVector(0.f, 55.f, 65.f);
	SpringArm->bUsePawnControlRotation=true;

	Camera=CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation=false;

	GetCharacterMovement()->bOrientRotationToMovement=true;
	GetCharacterMovement()->RotationRate=FRotator(0.0f,500.f,0.f);
	GetCharacterMovement()->MaxWalkSpeed=400.f;
	GetCharacterMovement()->BrakingDecelerationWalking=2000.f;

	HeroCombatComponent=CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombatComponent"));
	HeroUIComponent=CreateDefaultSubobject<UHeroUIComponent>(TEXT("HeroUIComponent"));
	
}

void ABAHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUpDataBase* LoadedData=CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(BAAbilitySystemComponent);
		}
	}
}

UPawnCombatComponent* ABAHeroCharacter::GetPawnCombatComponent() const
{
	return HeroCombatComponent;
}

UPawnUIComponent* ABAHeroCharacter::GetPawnUIComponent() const
{
	return HeroUIComponent;
}

UHeroUIComponent* ABAHeroCharacter::GetHeroUIComponent() const
{
	return HeroUIComponent;
}

void ABAHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	checkf(InputConfigDataAsset, TEXT("InputConfigDataAsset을 할당하지 않았습니다."));

	ULocalPlayer* LocalPlayer=GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem=LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext,0);

	UBAInputComponent* BAInputComponent=CastChecked<UBAInputComponent>(PlayerInputComponent);

	BAInputComponent->BindNativeInputAction(InputConfigDataAsset, BAGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	BAInputComponent->BindNativeInputAction(InputConfigDataAsset, BAGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);

	BAInputComponent->BindNativeInputAction(InputConfigDataAsset, BAGameplayTags::InputTag_PickUp_Weapon, ETriggerEvent::Started, this, &ThisClass::Input_PickUpWeaponStarted);

	BAInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);

	
}

void ABAHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.0f);

	if (MovementVector.Y !=0.f)
	{
		const FVector ForwardDirection=MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X !=0.f)
	{
		const FVector RightDirection=MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ABAHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector=InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X !=0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}

	if (LookAxisVector.Y !=0.f)
	{
		AddControllerYawInput(LookAxisVector.Y);
	}
}

void ABAHeroCharacter::Input_PickUpWeaponStarted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		BAGameplayTags::Player_Event_PickUp_Weapon,
		Data
	);
}

void ABAHeroCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	BAAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void ABAHeroCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	BAAbilitySystemComponent->OnAbilityInputReleased(InInputTag);	
}

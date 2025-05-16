// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EBAConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class EBAValidType : uint8
{
	Valid,
	Invalid
};

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand
};

UENUM()
enum class EBASuccessfulType : uint8
{
	Successful,
	Failed
};

UENUM()
enum class EBACountDownActionInput : uint8
{
	Start,
	Cancel
};

UENUM()
enum class EBACountDownActionOutput : uint8
{
	Updated,
	Completed,
	Cancelled
};
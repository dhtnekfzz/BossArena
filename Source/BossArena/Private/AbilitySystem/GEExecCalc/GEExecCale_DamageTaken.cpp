// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/GEExecCale_DamageTaken.h"

#include "BAGameplayTags.h"
#include "AbilitySystem/BAAttributeSet.h"

struct FBADamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken);

	FBADamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBAAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBAAttributeSet, DefensePower, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBAAttributeSet, DamageTaken, Target, false)
	}
};

static const FBADamageCapture& GetBADamageCapture()
{
	static FBADamageCapture BADamageCapture;
	return BADamageCapture;
}

UGEExecCale_DamageTaken::UGEExecCale_DamageTaken()
{
	RelevantAttributesToCapture.Add(GetBADamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetBADamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetBADamageCapture().DamageTakenDef);
}

void UGEExecCale_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec=ExecutionParams.GetOwningSpec();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags=EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags=EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower=0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetBADamageCapture().AttackPowerDef, EvaluateParameters,SourceAttackPower);

	float BaseDamage=0.f;
	int32 UsedLightAttackComboCount=0;
	int32 UsedHeavyAttackComboCount=0;

	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(BAGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage=TagMagnitude.Value;
		}

		if (TagMagnitude.Key.MatchesTagExact(BAGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackComboCount=TagMagnitude.Value;
		}

		if (TagMagnitude.Key.MatchesTagExact(BAGameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackComboCount=TagMagnitude.Value;
		}
	}

	float TargetDefensePower=0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetBADamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);

	if (UsedLightAttackComboCount!=0)
	{
		const float DamageIncreasePercentLight=(UsedLightAttackComboCount-1)*0.05f+1.f;
		BaseDamage*=DamageIncreasePercentLight;
	}

	if (UsedHeavyAttackComboCount!=0)
	{
		const float DamageIncreasePercentHeavy=(UsedHeavyAttackComboCount-1)*0.15f+1.f;
		BaseDamage*=DamageIncreasePercentHeavy;
	}

	const float FinalDamage=BaseDamage*SourceAttackPower/TargetDefensePower;

	if (FinalDamage>0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetBADamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamage
			)
		);
	}

	UE_LOG(LogTemp,Warning, TEXT("FinalDamage: %f"), FinalDamage);
	
}

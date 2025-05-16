// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BAEnumTypes.h"


/**
 * 
 */
class FBACountDownAction : public FPendingLatentAction
{
public:
	FBACountDownAction(float InTotalCountDownTime, float InUpdateInterval, float& InOutRemainingTime, EBACountDownActionOutput& InCountDownOutput, const FLatentActionInfo& InLatentInfo)
	:bNeedToCancel(false)
	,TotalCountDownTime(InTotalCountDownTime)
	,UpdateInterval(InUpdateInterval)
	,OutRemainingTime(InOutRemainingTime)
	,CountDownOutput(InCountDownOutput)
	,ExecutionFunction(InLatentInfo.ExecutionFunction)
	,OutputLink(InLatentInfo.Linkage)
	,CallbackTarget(InLatentInfo.CallbackTarget)
	,ElapsedInterval(0.f)
	,ElapsedTimeSinceStart(0.f)
	{
	}

	virtual void UpdateOperation(FLatentResponse& Response) override;

	void CancelAction();

private:
	bool bNeedToCancel;
	float TotalCountDownTime;
	float UpdateInterval;
	float& OutRemainingTime;
	EBACountDownActionOutput& CountDownOutput;
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;
	float ElapsedInterval;
	float ElapsedTimeSinceStart;
};

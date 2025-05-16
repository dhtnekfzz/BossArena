// Fill out your copyright notice in the Description page of Project Settings.


#include "BATypes/BACountDownAction.h"

void FBACountDownAction::UpdateOperation(FLatentResponse& Response)
{
	if (bNeedToCancel)
	{
		CountDownOutput=EBACountDownActionOutput::Cancelled;

		Response.FinishAndTriggerIf(true,ExecutionFunction,OutputLink,CallbackTarget);

		return;
	}

	if (ElapsedTimeSinceStart>=TotalCountDownTime)
	{
		CountDownOutput=EBACountDownActionOutput::Completed;

		Response.FinishAndTriggerIf(true,ExecutionFunction,OutputLink,CallbackTarget);

		return;
	}

	if (ElapsedTimeSinceStart < UpdateInterval)
	{
		ElapsedInterval+=Response.ElapsedTime();
	}
	else
	{
		ElapsedTimeSinceStart+=UpdateInterval>0.f?UpdateInterval:Response.ElapsedTime();

		OutRemainingTime =TotalCountDownTime-ElapsedTimeSinceStart;

		CountDownOutput=EBACountDownActionOutput::Updated;

		Response.TriggerLink(ExecutionFunction,OutputLink,CallbackTarget);

		ElapsedInterval=0.f;
	}
	
}

void FBACountDownAction::CancelAction()
{
	bNeedToCancel=true;
}

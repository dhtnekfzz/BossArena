// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/BAWidgetBase.h"

#include "Interfaces/PawnUIInterface.h"

void UBAWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IPawnUIInterface* PawnUIInterface=Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (UHeroUIComponent* HeroUIComponent=PawnUIInterface->GetHeroUIComponent())
		{
			BP_OnOwningHeroUIComponentInitialized(HeroUIComponent);
		}
	}
}

void UBAWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
	if (IPawnUIInterface* PawnUIInterface=Cast<IPawnUIInterface>(OwningEnemyActor))
	{
		UEnemyUIComponent* EnemyUIComponent=PawnUIInterface->GetEnemyUIComponent();

		BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
	}
}

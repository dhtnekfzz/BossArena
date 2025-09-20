// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/BAAttributeSet.h"

#include "BAFunctionLibrary.h"
#include "BAGameplayTags.h"
#include "GameplayEffectExtension.h"
#include "Components/UI/HeroUIComponent.h"
#include "Components/UI/PawnUIComponent.h"
#include "Interfaces/PawnUIInterface.h"
#include "Net/UnrealNetwork.h"

UBAAttributeSet::UBAAttributeSet()
{
}

void UBAAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	UAttributeSet::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UBAAttributeSet, CurrentHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBAAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UBAAttributeSet, CurrentRage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBAAttributeSet, MaxRage, COND_None, REPNOTIFY_Always);

	
}

void UBAAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface=TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}
	
	UPawnUIComponent* PawnUIComponent=CachedPawnUIInterface->GetPawnUIComponent();

	if (Data.EvaluatedData.Attribute==GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth=FMath::Clamp(GetCurrentHealth(),0.f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth()/GetMaxHealth());
	}

	if (Data.EvaluatedData.Attribute==GetCurrentRageAttribute())
	{
		const float NewCurrentRage=FMath::Clamp(GetCurrentRage(),0.f, GetMaxRage());

		SetCurrentRage(NewCurrentRage);

		if (GetCurrentRage()==GetMaxRage())
		{
			UBAFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(),BAGameplayTags::Player_Status_Rage_Full);

			//GetOwningAbilitySystemComponent()->AddReplicatedLooseGameplayTag(BAGameplayTags::Player_Status_Rage_Full);
		}
		else if (GetCurrentRage()==0.f)
		{
			UBAFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(),BAGameplayTags::Player_Status_Rage_None);
		}
		else
		{
			UBAFunctionLibrary::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(),BAGameplayTags::Player_Status_Rage_Full);
			UBAFunctionLibrary::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(),BAGameplayTags::Player_Status_Rage_None);
		}
		
		if (UHeroUIComponent* HeroUIComponent=CachedPawnUIInterface->GetHeroUIComponent())
		{
			HeroUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentRage()/GetMaxRage());
		}
	
	}

	if (Data.EvaluatedData.Attribute==GetDamageTakenAttribute())
	{
		const float OldHealth=GetCurrentHealth();
		const float DamageDone=GetDamageTaken();

		const float NewCurrentHealth=FMath::Clamp(OldHealth-DamageDone,0.f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth()/GetMaxHealth());
		
		if (GetCurrentHealth()==0.f)
		{
			UBAFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), BAGameplayTags::Shared_Status_Dead);
		}
	}

}

void UBAAttributeSet::OnRep_HealthChanged(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBAAttributeSet, CurrentHealth, OldHealth);

	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(GetOwningActor());
	}
	if (UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent())
	{
		const float MaxHealthValue = GetMaxHealth();
		if (MaxHealthValue > 0.f)
		{
			PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / MaxHealthValue);
		}
	}
}

void UBAAttributeSet::OnRep_RageChanged(const FGameplayAttributeData& OldRage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBAAttributeSet, CurrentRage, OldRage);
	
	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(GetOwningActor());
	}

	if (UHeroUIComponent* HeroUIComponent=CachedPawnUIInterface->GetHeroUIComponent())
	{
		HeroUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentRage()/GetMaxRage());
	}
}

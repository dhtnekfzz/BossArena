// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BAHeroController.h"

ABAHeroController::ABAHeroController()
{
	HeroTeamID=FGenericTeamId(0);
}

FGenericTeamId ABAHeroController::GetGenericTeamId() const
{
	return HeroTeamID;
}


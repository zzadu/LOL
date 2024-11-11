// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LOLMonster.h"

void ALOLMonster::SetDead()
{
	Super::SetDead();

	Destroy();
}

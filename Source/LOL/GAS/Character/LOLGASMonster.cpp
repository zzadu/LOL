// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Character/LOLGASMonster.h"
#include "AbilitySystemComponent.h"
#include "GAS/Attribute/LOLCharacterAttributeSet.h"

ALOLGASMonster::ALOLGASMonster()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	AttributeSet = CreateDefaultSubobject<ULOLCharacterAttributeSet>(TEXT("CharacterAttributeSet"));
}

class UAbilitySystemComponent* ALOLGASMonster::GetAbilitySystemComponent() const
{
	return ASC;
}


void ALOLGASMonster::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ASC->InitAbilityActorInfo(this, this);
}
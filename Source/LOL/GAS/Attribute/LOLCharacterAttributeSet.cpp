// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attribute/LOLCharacterAttributeSet.h"
#include "LOL.h"

ULOLCharacterAttributeSet::ULOLCharacterAttributeSet()
	: AttackRange(525.0f),
	MaxAttackRange(300.0f),
	AttackRate(30.f),
	MaxAttackRate(100.f),
	MaxHealth(100.0f)
{
	InitHealth(GetMaxHealth());
}

void ULOLCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	//Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
}

void ULOLCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	//Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		LOL_LOG(LogLOL, Log, TEXT("Health: %f -> %f"), OldValue, NewValue);
	}
}

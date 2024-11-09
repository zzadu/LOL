// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attribute/LOLCharacterAttributeSet.h"
#include "LOL.h"
#include "GameplayEffectExtension.h"

ULOLCharacterAttributeSet::ULOLCharacterAttributeSet()
	: Level(0.0f),
	Experience(0.0f),
	MaxExperience(100.0f),
	Mana(0.0f),
	MaxMana(100.0f),
	AttackRange(525.0f),
	MaxAttackRange(300.0f),
	AttackRate(30.f),
	MaxAttackRate(100.f),
	MaxHealth(100.0f),
	Damage(0.0f)
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

	if (Attribute == GetDamageAttribute())
	{
		NewValue = NewValue < 0.0f ? 0.0f : NewValue;
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

void ULOLCharacterAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	float MinimumHealth = 0.0f;

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		LOL_LOG(LogLOL, Warning, TEXT("Direct Health Access: %f"), GetHealth());
		SetHealth(FMath::Clamp(GetHealth(), MinimumHealth, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		LOL_LOG(LogLOL, Log, TEXT("Damage: %f"), GetDamage());
		SetHealth(FMath::Clamp(GetHealth() - GetDamage(), MinimumHealth, GetMaxHealth()));
		SetDamage(0.0f);
	}
}

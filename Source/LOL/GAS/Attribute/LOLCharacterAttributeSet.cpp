// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attribute/LOLCharacterAttributeSet.h"
#include "LOL.h"
#include "GameplayEffectExtension.h"
#include "Tag/LOLGameplayTag.h"

ULOLCharacterAttributeSet::ULOLCharacterAttributeSet()
	: Level(0.0f),
	Experience(0.0f),
	MaxExperience(0.0f),
	Mana(0.0f),
	MaxMana(0.0f),
	ManaRegen(0.0f),
	MoveSpeed(0.0f),
	HealthRegen(0.0f),
	AttackRange(0.0f),
	MaxAttackRange(0.0f),
	AttackDamage(0.0f),
	AttackSpeed(0.0f),
	AbilityPower(0.0f),
	AbilityHaste(0.0f),
	CriticalStrikeChance(0.0f),
	CriticalStrikeDamage(0.0f),
	Lethality(0.0f),
	MagicPenetration(0.0f),
	Armor(0.0f),
	MagicResistance(0.0f),
	Tenecity(0.0f),
	MaxAttackDamage(0.f),
	MaxHealth(0.0f),
	Damage(0.0f)
{
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

bool ULOLCharacterAttributeSet::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data)
{
	if (!Super::PreGameplayEffectExecute(Data))
	{
		return false;
	}

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		if (Data.EvaluatedData.Magnitude > 0.0f)
		{
			if (Data.Target.HasMatchingGameplayTag(LOLTAG_CHARACTER_INVINCIBLE))
			{
				Data.EvaluatedData.Magnitude = 0.0f;
				return false;
			}
		}
	}

	
	return true;
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

	if (GetHealth() <= 0.0f && !bOutOfHealth)
	{
		Data.Target.AddLooseGameplayTag(LOLTAG_CHARACTER_ISDEAD);
		OnOutOfHealth.Broadcast();
	}

	bOutOfHealth = GetHealth() <= 0.0f;
}

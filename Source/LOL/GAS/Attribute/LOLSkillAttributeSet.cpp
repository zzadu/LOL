// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attribute/LOLSkillAttributeSet.h"
#include "LOL.h"

ULOLSkillAttributeSet::ULOLSkillAttributeSet()
	: Level(0.0f),
	SkillRange(0.f),
	MaxSkillRange(0.f),
	SkillRadius(0.f),
	MaxSkillRadius(0.f),
	SkillAttackDamage(0.f),
	MaxSkillAttackDamage(0.f),
	SkillAbilityPowerDamage(0.0f),
	MaxSkillAbilityPowerDamage(0.0f),
	ManaComsumption(0.0f),
	Cooldown(0.0f),
	MoveSpeed(0.0f),
	AttackSpeed(0.0f)
{
}

void ULOLSkillAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	//Super::PreAttributeChange(Attribute, NewValue);

}

void ULOLSkillAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	//Super::PostAttributeChange(Attribute, OldValue, NewValue);
	if (Attribute == GetSkillRangeAttribute())
	{
		LOL_LOG(LogLOL, Log, TEXT("Skill Range: %f -> %f"), OldValue, NewValue);
	}
	else if (Attribute == GetSkillRadiusAttribute())
	{
		LOL_LOG(LogLOL, Log, TEXT("Skill Radius: %f -> %f"), OldValue, NewValue);
	}
	else if (Attribute == GetSkillAttackDamageAttribute())
	{
		LOL_LOG(LogLOL, Log, TEXT("Skill Rate: %f -> %f"), OldValue, NewValue);
	}
}

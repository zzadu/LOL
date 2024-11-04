// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attribute/LOLSkillAttributeSet.h"
#include "LOL.h"

ULOLSkillAttributeSet::ULOLSkillAttributeSet()
	: SkillRange(300.f),
	MaxSkillRange(500.f),
	SkillRadius(50.f),
	MaxSkillRadius(100.f),
	SkillRate(50.f),
	MaxSkillRate(100.f)
{
}

void ULOLSkillAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	//Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetSkillRangeAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxSkillRange());
	}
	else if (Attribute == GetSkillRadiusAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxSkillRadius());
	}
	else if (Attribute == GetSkillRateAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxSkillRate());
	}
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
	else if (Attribute == GetSkillRateAttribute())
	{
		LOL_LOG(LogLOL, Log, TEXT("Skill Rate: %f -> %f"), OldValue, NewValue);
	}
}

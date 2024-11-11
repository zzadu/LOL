// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "LOLSkillAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class LOL_API ULOLSkillAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	ULOLSkillAttributeSet();

	ATTRIBUTE_ACCESSORS(ULOLSkillAttributeSet, Level);
	ATTRIBUTE_ACCESSORS(ULOLSkillAttributeSet, SkillRange);
	ATTRIBUTE_ACCESSORS(ULOLSkillAttributeSet, MaxSkillRange);
	ATTRIBUTE_ACCESSORS(ULOLSkillAttributeSet, SkillRadius);
	ATTRIBUTE_ACCESSORS(ULOLSkillAttributeSet, MaxSkillRadius);
	ATTRIBUTE_ACCESSORS(ULOLSkillAttributeSet, SkillAttackDamage);
	ATTRIBUTE_ACCESSORS(ULOLSkillAttributeSet, MaxSkillAttackDamage);
	ATTRIBUTE_ACCESSORS(ULOLSkillAttributeSet, SkillAbilityPowerDamage);
	ATTRIBUTE_ACCESSORS(ULOLSkillAttributeSet, MaxSkillAbilityPowerDamage);
	ATTRIBUTE_ACCESSORS(ULOLSkillAttributeSet, ManaComsumption);
	ATTRIBUTE_ACCESSORS(ULOLSkillAttributeSet, Cooldown);
	ATTRIBUTE_ACCESSORS(ULOLSkillAttributeSet, MoveSpeed);
	ATTRIBUTE_ACCESSORS(ULOLSkillAttributeSet, AttackSpeed);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Level;
	
	UPROPERTY(BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData SkillRange;

	UPROPERTY(BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxSkillRange;

	UPROPERTY(BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData SkillRadius;

	UPROPERTY(BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxSkillRadius;

	UPROPERTY(BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData SkillAttackDamage;

	UPROPERTY(BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxSkillAttackDamage;

	UPROPERTY(BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData SkillAbilityPowerDamage;

	UPROPERTY(BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxSkillAbilityPowerDamage;

	UPROPERTY(BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData ManaComsumption;

	UPROPERTY(BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Cooldown;

	UPROPERTY(BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MoveSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData AttackSpeed;
	
};

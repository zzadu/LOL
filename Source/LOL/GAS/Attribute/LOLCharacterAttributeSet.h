// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "LOLCharacterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class LOL_API ULOLCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	ULOLCharacterAttributeSet();

	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, Level);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, Experience);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, MaxExperience);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, Mana);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, MaxMana);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, AttackRange);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, MaxAttackRange);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, AttackRate);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, MaxAttackRate);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, Damage);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Level;

	UPROPERTY(BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Experience;

	UPROPERTY(BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxExperience;

	UPROPERTY(BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Mana;

	UPROPERTY(BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxMana;
	
	UPROPERTY(BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Damage;
	
	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData AttackRange;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxAttackRange;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData AttackRate;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxAttackRate;

};

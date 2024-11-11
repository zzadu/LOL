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

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOutOfHealthDelegate);

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
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, ManaRegen);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, MaxManaRegen);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, MoveSpeed);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, MaxMoveSpeed);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, AttackRange);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, MaxAttackRange);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, AttackDamage);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, MaxAttackDamage);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, AttackSpeed);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, MaxAttackSpeed);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, CriticalStrikeChance);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, MaxCriticalStrikeChance);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, CriticalStrikeDamage);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, MaxCriticalStrikeDamage);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, Lethality);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, MaxLethality);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, AbilityPower);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, MaxAbilityPower);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, AbilityHaste);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, MaxAbilityHaste);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, MagicPenetration);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, MaxMagicPenetration);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, HealthRegen);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, MaxHealthRegen);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, Damage);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, Armor);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, MaxArmor);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, MagicResistance);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, MaxMagicResistance);

	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, Tenecity);
	ATTRIBUTE_ACCESSORS(ULOLCharacterAttributeSet, MaxTenecity);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	mutable FOutOfHealthDelegate OnOutOfHealth;

protected:
	// stat
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

	UPROPERTY(BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData ManaRegen;

	UPROPERTY(BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxManaRegen;

	UPROPERTY(BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MoveSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxMoveSpeed;

	// health
	UPROPERTY(BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxHealth;
	
	UPROPERTY(BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData HealthRegen;

	UPROPERTY(BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxHealthRegen;

	// attack
	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Damage;
	
	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData AttackRange;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxAttackRange;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData AttackDamage;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxAttackDamage;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData AttackSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxAttackSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData AbilityPower;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxAbilityPower;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData AbilityHaste;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxAbilityHaste;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData CriticalStrikeChance;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxCriticalStrikeChance;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData CriticalStrikeDamage;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxCriticalStrikeDamage;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Lethality;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxLethality;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MagicPenetration;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxMagicPenetration;
	
	// defense
	UPROPERTY(BlueprintReadOnly, Category = "Defense", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Armor;

	UPROPERTY(BlueprintReadOnly, Category = "Defense", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxArmor;

	UPROPERTY(BlueprintReadOnly, Category = "Defense", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MagicResistance;

	UPROPERTY(BlueprintReadOnly, Category = "Defense", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxMagicResistance;

	UPROPERTY(BlueprintReadOnly, Category = "Defense", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Tenecity;

	UPROPERTY(BlueprintReadOnly, Category = "Defense", meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxTenecity;

	bool bOutOfHealth = false;

};

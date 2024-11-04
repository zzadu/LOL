// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "LOLGA_AutoAttackDamage.generated.h"

/**
 * 
 */
UCLASS()
class LOL_API ULOLGA_AutoAttackDamage : public UGameplayAbility
{
	GENERATED_BODY()

public:
	ULOLGA_AutoAttackDamage();

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UFUNCTION()
	void GiveDamage();
};

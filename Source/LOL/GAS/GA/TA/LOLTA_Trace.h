// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "LOLTA_Trace.generated.h"

/**
 * 
 */
UCLASS()
class LOL_API ALOLTA_Trace : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
	ALOLTA_Trace();

	virtual void StartTargeting(UGameplayAbility* Ability) override;

	virtual void ConfirmTargetingAndContinue() override;

	void SetShowDebug(bool InShowDebug) { bShowDebug = InShowDebug; }

protected:
	virtual FGameplayAbilityTargetDataHandle MakeTargetData() const;

	bool bShowDebug = false;
};

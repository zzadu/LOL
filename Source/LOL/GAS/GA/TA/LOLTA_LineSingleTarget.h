// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GA/TA/LOLTA_TraceBase.h"
#include "LOLTA_LineSingleTarget.generated.h"

/**
 * 
 */
UCLASS()
class LOL_API ALOLTA_LineSingleTarget : public ALOLTA_TraceBase
{
	GENERATED_BODY()

public:
	ALOLTA_LineSingleTarget();

protected:
	virtual FGameplayAbilityTargetDataHandle MakeTargetData() const override;

	bool bShowDebug = false;
};

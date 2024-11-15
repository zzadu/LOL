// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LOLTA_TraceBase.h"
#include "LOLTA_SingleTarget.generated.h"

/**
 * 
 */
UCLASS()
class LOL_API ALOLTA_SingleTarget : public ALOLTA_TraceBase
{
	GENERATED_BODY()

public:
	ALOLTA_SingleTarget();

protected:
	virtual FGameplayAbilityTargetDataHandle MakeTargetData() const override;

	bool bShowDebug = false;
};

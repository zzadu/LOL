// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LOLTA_TraceBase.h"
#include "LOLTA_SphereMultiTarget.generated.h"

/**
 * 
 */
UCLASS()
class LOL_API ALOLTA_SphereMultiTarget : public ALOLTA_TraceBase
{
	GENERATED_BODY()

public:
	ALOLTA_SphereMultiTarget();

protected:
	virtual FGameplayAbilityTargetDataHandle MakeTargetData() const override;
};

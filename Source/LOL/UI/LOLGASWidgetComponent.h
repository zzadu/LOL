// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "LOLGASWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class LOL_API ULOLGASWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	ULOLGASWidgetComponent();
	virtual void InitWidget() override;
};

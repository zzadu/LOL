// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystemInterface.h"
#include "LOLGASUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOL_API ULOLGASUserWidget : public UUserWidget, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	virtual void SetAbilitySystemComponent(AActor* InOwner);
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;
};

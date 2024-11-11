// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LOLMonster.h"
#include "AbilitySystemInterface.h"
#include "LOLGASMonster.generated.h"

/**
 * 
 */
UCLASS()
class LOL_API ALOLGASMonster : public ALOLMonster, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ALOLGASMonster();

public:
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void PossessedBy(AController* NewController) override;

protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY()
	TObjectPtr<class ULOLCharacterAttributeSet> AttributeSet;
	
	// widget
protected:
	UPROPERTY(VisibleAnywhere);
	TObjectPtr<class ULOLGASWidgetComponent> HpBar;

	UFUNCTION()
	virtual void OnOutOfHealth();
};

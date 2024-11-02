// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LOLCharacter.h"
#include "LOLPlayer.generated.h"


/**
 * 
 */
UCLASS()
class LOL_API ALOLPlayer : public ALOLCharacter
{
	GENERATED_BODY()

public:
	ALOLPlayer();

protected:
	virtual void PossessedBy(AController* NewController) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCameraComponent> Camera;

	// UPROPERTY(VisibleAnywhere)
	// TObjectPtr<class ULOLWidgetComponent> HpBar;

	TObjectPtr<class ALOLPlayerController> LOLPlayerController;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category=Attribute)
	TArray<UCurveTable*> CurveData;
	

};

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

public:
	class ALOLPlayerController* GetController();
	
protected:
	TObjectPtr<class ALOLPlayerController> LOLPlayerController;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category=Attribute)
	TArray<UCurveTable*> CurveData;

	// Dead
	virtual void SetDead() override;

protected:
	bool IsDefault = true;

	// 무기 변경
public:
	UFUNCTION(BlueprintCallable)
	void SetIsDefault(bool NewIsDefault) {this->IsDefault = NewIsDefault;}

	UFUNCTION(BlueprintCallable)
	bool GetIsDefault() {return this->IsDefault;}

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LOLPlayerController.generated.h"

class UAbilitySystemComponent;
class UInputMappingContext;

#define SKILL_Q	0;
#define SKILL_W 1;
#define SKILL_E 2;
#define SKILL_R 3;

#define SPELL_D 4;
#define SPELL_F	5;

#define AUTO_ATTACK	10;


/**
 * 
 */
UCLASS()
class LOL_API ALOLPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ALOLPlayerController();

public:
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	void SetupInputMappingContext();
	virtual void SetupInputComponent() override;
	void SetupGASInputComponent();
	
	// Input Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> InputMappingContext;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> AutoAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> SkillAction;

	// Move
	TObjectPtr<class ALOLPlayer> TargetActor;
	
	void Move();
	void AutoAttack(class AActor* Target);
	void EndAutoAttack();

	// Pawn
	protected:
	TObjectPtr<class ALOLGASPlayer> LOLPlayer;

	// ASC
protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	void GASInputPressed(int32 InputId);
	void GASInputReleased(int32 InputId);
	
};

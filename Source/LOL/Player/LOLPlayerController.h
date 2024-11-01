// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LOLPlayerController.generated.h"

class UInputMappingContext;
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
	void SetupInputMappingContext();
	virtual void SetupInputComponent() override;
	
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

	void Move();
	void Attack(class AActor* Target);

	// Pawn
	protected:
	TObjectPtr<class ALOLPlayer> LOLPlayer;
	
};

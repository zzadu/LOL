// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LOLCharacter.generated.h"

UCLASS()
class LOL_API ALOLCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALOLCharacter();

public:
	FORCEINLINE virtual class UAnimMontage* GetAutoAttackActionMontage() const { return AutoAttackActionMontage; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GAS)
	TObjectPtr<class UAnimMontage> AutoAttackActionMontage;


	// Dead Section
protected:
	virtual void SetDead();
	void PlayDeadAnimation();

	float DeadEventDelayTime = 5.0f;

};

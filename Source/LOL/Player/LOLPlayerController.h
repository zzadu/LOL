// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTags.h"
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
	void OnLearnSkill(int32 InputId);
	
	// Input Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> InputMappingContext;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class UInputAction>> LearnActions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class UInputAction>> SkillActions;

	// Move & Auto Attack
public:
	class ALOLCharacter* GetTargetActor();
	void SetTargetActor(ALOLCharacter* InTargetActor);

protected:
	TObjectPtr<class ALOLCharacter> TargetActor;
	
	bool CanAttack();
	void Move();
	void AutoAttack();

protected:
	UPROPERTY(EditAnywhere, Category = GAS, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UGameplayEffect> LevelUpEffect;

	UPROPERTY(EditAnywhere, Category = Tag, Meta=(Categories=Event))
	FGameplayTag LevelUpTag;
	
	void LevelUp();
	
public:
	void LookAt(FVector Location);
	
	// Pawn
protected:
	TObjectPtr<class ALOLGASPlayer> LOLPlayer;

	// ASC
protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY(EditAnywhere, Category = Attribute)
	const class ULOLCharacterAttributeSet* AttributeSet;

	void GASInputPressed(int32 InputId);
	void GASInputReleased(int32 InputId);
	
};

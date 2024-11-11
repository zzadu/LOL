// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "LOLGA_SkillBase.generated.h"

/**
 * 
 */
UCLASS()
class LOL_API ULOLGA_SkillBase : public UGameplayAbility
{
	GENERATED_BODY()

public:
	ULOLGA_SkillBase();

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
protected:
	UFUNCTION()
	virtual void OnCompleteCallback();

	UFUNCTION()
	virtual void OnInterruptedCallback();

protected:
	UPROPERTY()
	TObjectPtr<class ULOLSkillAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, Category = GAS, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UGameplayEffect> LevelUpEffect;

public:
	UFUNCTION()
	void LevelUp(ALOLGASPlayer* AvatarActor);
	
};

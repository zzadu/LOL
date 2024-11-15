// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "LOLGA_SkillAttackHitCheck.generated.h"

/**
 * 
 */
UCLASS()
class LOL_API ULOLGA_SkillAttackHitCheck : public UGameplayAbility
{
	GENERATED_BODY()

public:
	ULOLGA_SkillAttackHitCheck();

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UFUNCTION()
	void OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetData);

public:
	UPROPERTY(EditAnywhere, Category = GAS, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UGameplayEffect> SkillEffect;

	UPROPERTY(EditAnywhere, Category = GAS, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UGameplayEffect> Buff;
	
	int32 CurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillType", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AGameplayAbilityTargetActor> TargetActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillType", meta = (AllowPrivateAccess = "true"))
	bool isTargeting = false;
};
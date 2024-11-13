// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GA/Skill/LOLGA_SkillBase.h"
#include "LOLGA_ChangeMontage.generated.h"

/**
 * 
 */
UCLASS()
class LOL_API ULOLGA_ChangeMontage : public ULOLGA_SkillBase
{
	GENERATED_BODY()

public:
	ULOLGA_ChangeMontage();

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	UFUNCTION()
	void ChangeMesh();

protected:
	UPROPERTY()
	TObjectPtr<class UAnimMontage> DefaultMontage;
	
	UPROPERTY(EditAnywhere, Category = Mesh)
	TObjectPtr<class UAnimMontage> NewMontage;

	bool isDefault = true;
};

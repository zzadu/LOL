// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/LOLGA_AutoAttackDamage.h"
#include "LOL.h"

ULOLGA_AutoAttackDamage::ULOLGA_AutoAttackDamage()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void ULOLGA_AutoAttackDamage::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	LOL_LOG(LogLOL, Log, TEXT("Begin"));
	
	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/LOLGA_SkillAttackHitCheck.h"
#include "LOL.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/GA/AT/LOLAT_Trace.h"
#include "GAS/GA/TA/LOLTA_Trace.h"

ULOLGA_SkillAttackHitCheck::ULOLGA_SkillAttackHitCheck()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void ULOLGA_SkillAttackHitCheck::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (isTargeting && !isMultiTargeting)
	{
		ULOLAT_Trace* SkillAttackTraceTask = ULOLAT_Trace::CreateTask(this, ALOLTA_Trace::StaticClass(), isTargeting, isMultiTargeting);
		SkillAttackTraceTask->OnComplete.AddDynamic(this, &ULOLGA_SkillAttackHitCheck::OnTraceResultCallback);
		SkillAttackTraceTask->ReadyForActivation();
	}
}

void ULOLGA_SkillAttackHitCheck::OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	if (UAbilitySystemBlueprintLibrary::TargetDataHasHitResult(TargetDataHandle, 0))
	{
		FHitResult HitResult = UAbilitySystemBlueprintLibrary::GetHitResultFromTargetData(TargetDataHandle, 0);
		LOL_LOG(LogLOL, Log, TEXT("Target %s Detected"), *HitResult.GetActor()->GetName());
	}

	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/LOLGA_AutoAttack.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/Character/LOLGASPlayer.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "LOL.h"

ULOLGA_AutoAttack::ULOLGA_AutoAttack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void ULOLGA_AutoAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                        const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	LOL_LOG(LogLOL, Log, TEXT("Begin"));

	ALOLCharacter* LOLCharacter = CastChecked<ALOLCharacter>(ActorInfo->AvatarActor.Get());

	UAbilityTask_PlayMontageAndWait* PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayAttack"), LOLCharacter->GetAutoAttackActionMontage(), 1.0f);
	PlayAttackTask->OnCompleted.AddDynamic(this, &ULOLGA_AutoAttack::OnCompleteCallback);
	PlayAttackTask->OnInterrupted.AddDynamic(this, &ULOLGA_AutoAttack::OnInterruptedCallback);
	PlayAttackTask->ReadyForActivation();
}

void ULOLGA_AutoAttack::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void ULOLGA_AutoAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	LOL_LOG(LogLOL, Log, TEXT("End"));
}

void ULOLGA_AutoAttack::InputPressed(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	LOL_LOG(LogLOL, Log, TEXT("Begin"));
}

void ULOLGA_AutoAttack::OnCompleteCallback()
{
	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void ULOLGA_AutoAttack::OnInterruptedCallback()
{
	bool bReplicateEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

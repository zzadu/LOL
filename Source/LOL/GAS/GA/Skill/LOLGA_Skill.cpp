// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/Skill/LOLGA_Skill.h"
#include "LOL.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/LOLCharacter.h"
#include "GAS/Character/LOLGASPlayer.h"

ULOLGA_Skill::ULOLGA_Skill()
{
}

void ULOLGA_Skill::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	LOL_LOG(LogLOL, Log, TEXT("Begin"));

	ALOLGASPlayer* LOLGASPlayer = CastChecked<ALOLGASPlayer>(ActorInfo->AvatarActor.Get());

	UAbilityTask_PlayMontageAndWait* PlaySkillTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlaySkill"), LOLGASPlayer->GetSkillActionMontage(GetCurrentAbilitySpec()->InputID), 1.0f);
	PlaySkillTask->OnCompleted.AddDynamic(this, &ULOLGA_Skill::OnCompleteCallback);
	PlaySkillTask->OnInterrupted.AddDynamic(this, &ULOLGA_Skill::OnInterruptedCallback);
	PlaySkillTask->ReadyForActivation();
}

void ULOLGA_Skill::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void ULOLGA_Skill::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	LOL_LOG(LogLOL, Log, TEXT("End"));
}

void ULOLGA_Skill::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
}

void ULOLGA_Skill::OnCompleteCallback()
{
	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void ULOLGA_Skill::OnInterruptedCallback()
{
	bool bReplicateEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

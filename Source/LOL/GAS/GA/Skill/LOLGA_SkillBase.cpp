// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/Skill/LOLGA_SkillBase.h"
#include "AbilitySystemComponent.h"
#include "GAS/Attribute/LOLSkillAttributeSet.h"
#include "LOL.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GAS/Character/LOLGASPlayer.h"

ULOLGA_SkillBase::ULOLGA_SkillBase()
{
	AttributeSet = CreateDefaultSubobject<ULOLSkillAttributeSet>(TEXT("SkillAttributeSet"));
}

void ULOLGA_SkillBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	LOL_LOG(LogLOL, Log, TEXT("Begin"));

	ALOLGASPlayer* LOLGASPlayer = CastChecked<ALOLGASPlayer>(ActorInfo->AvatarActor.Get());

	UAbilityTask_PlayMontageAndWait* PlaySkillTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlaySkill"), LOLGASPlayer->GetSkillActionMontage(GetCurrentAbilitySpec()->InputID), 1.0f);
	PlaySkillTask->OnCompleted.AddDynamic(this, &ULOLGA_SkillBase::OnCompleteCallback);
	PlaySkillTask->OnInterrupted.AddDynamic(this, &ULOLGA_SkillBase::OnInterruptedCallback);
	PlaySkillTask->ReadyForActivation();
}

void ULOLGA_SkillBase::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void ULOLGA_SkillBase::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	LOL_LOG(LogLOL, Log, TEXT("End"));
}

void ULOLGA_SkillBase::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
}

void ULOLGA_SkillBase::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	LOL_LOG(LogLOL, Log, TEXT("Give"));
	
	ALOLGASPlayer* LOLGASPlayer = CastChecked<ALOLGASPlayer>(ActorInfo->AvatarActor.Get());
	LOLGASPlayer->OnSkillLevelUp.AddDynamic(this, &ULOLGA_SkillBase::LevelUp);
}

void ULOLGA_SkillBase::OnCompleteCallback()
{
	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void ULOLGA_SkillBase::OnInterruptedCallback()
{
	bool bReplicateEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void ULOLGA_SkillBase::LevelUp(ALOLGASPlayer* AvatarActor)
{
	UAbilitySystemComponent* ASC = AvatarActor->GetAbilitySystemComponent();

	FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(LevelUpEffect, AttributeSet->GetLevel() + 1, EffectContextHandle);
	if (EffectSpecHandle.IsValid())
	{
		ASC->BP_ApplyGameplayEffectSpecToSelf(EffectSpecHandle);
	}
}

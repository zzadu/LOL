// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/Skill/LOLGA_SkillBase.h"
#include "AbilitySystemComponent.h"
#include "GAS/Attribute/LOLSkillAttributeSet.h"
#include "LOL.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GAS/Character/LOLGASPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/LOLPlayerController.h"


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

	LOLGASPlayer = CastChecked<ALOLGASPlayer>(ActorInfo->AvatarActor.Get());

	if (!LOLGASPlayer)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}
	
	ActiveSkillActionMontage = LOLGASPlayer->GetSkillActionMontage(GetCurrentAbilitySpec()->InputID);
	if (!ActiveSkillActionMontage)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}

	LOLGASPlayer->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	ALOLPlayerController* PC = Cast<ALOLPlayer>(ActorInfo->AvatarActor.Get())->GetController();
	if (!PC)
	{
		LOL_LOG(LogLOL, Error, TEXT("LOLPlayerController not found!"));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}
	FHitResult Hit;
	bool bHitSuccessful = PC->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, OUT Hit);

	Hit.Location.Z = ActorInfo->AvatarActor.Get()->GetActorLocation().Z;
	PC->LookAt(Hit.Location);

	UAbilityTask_PlayMontageAndWait* PlayMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, FName(FString::Printf(TEXT("%d"), GetAbilityLevel())), ActiveSkillActionMontage, 1.0f);
	PlayMontageTask->OnCompleted.AddDynamic(this, &ULOLGA_SkillBase::OnCompleteCallback);
	PlayMontageTask->OnInterrupted.AddDynamic(this, &ULOLGA_SkillBase::OnInterruptedCallback);
	PlayMontageTask->ReadyForActivation();

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
	if (LOLGASPlayer)
	{
		LOLGASPlayer->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}
	
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
	
	LOLGASPlayer = CastChecked<ALOLGASPlayer>(ActorInfo->AvatarActor.Get());
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

void ULOLGA_SkillBase::LevelUp()
{
	if (isUlt && GetAbilityLevel() >= 4)
	{
		return;
	}
	if (!isUlt && GetAbilityLevel() >= 6)
	{
		return;
	}
	
	UAbilitySystemComponent* ASC = LOLGASPlayer->GetAbilitySystemComponent();

	FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(LevelUpEffect, GetAbilityLevel(), EffectContextHandle);
	if (EffectSpecHandle.IsValid())
	{
		ASC->BP_ApplyGameplayEffectSpecToSelf(EffectSpecHandle);
	}
}

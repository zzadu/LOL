// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/LOLGA_AutoAttackDamage.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "LOL.h"
#include "GAS/Attribute/LOLCharacterAttributeSet.h"
#include "GAS/Character/LOLGASPlayer.h"
#include "Player/LOLPlayerController.h"

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

	GiveDamage();
	
}

void ULOLGA_AutoAttackDamage::GiveDamage()
{
	ALOLGASPlayer* SourceActor = Cast<ALOLGASPlayer>(GetActorInfo().AvatarActor.Get());

	ALOLPlayerController* PC = SourceActor->GetController();
	if (!PC)
	{
		LOL_LOG(LogLOL, Error, TEXT("LOLPlayerController not found!"));
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}

	FHitResult Hit;
	bool bHitSuccessful = PC->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, OUT Hit);

	if (bHitSuccessful)
	{
		if (ALOLCharacter* TargetActor = Cast<ALOLCharacter>(Hit.GetActor()))
		{
			//FGameplayAbilityTargetData* TargetData = new FGameplayAbilityTargetData();
			//FGameplayAbilityTargetData_SingleTargetHit * Data = new FGameplayAbilityTargetData_SingleTargetHit();
			FGameplayAbilityTargetData_ActorArray* TargetData = new FGameplayAbilityTargetData_ActorArray();
			TargetData->SetActors({ TargetActor });
			//Data->SetActors({TargetActor});
			TargetData->SetActors({TargetActor});
			FGameplayAbilityTargetDataHandle DataHandle;
			DataHandle.Add(TargetData);

			FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(AttackDamageEffect);
			if (EffectSpecHandle.IsValid())
			{
				ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle, DataHandle);
			}
		}
	}
	
	// FGameplayAbilityTargetData* TargetData = new FGameplayAbilityTargetData();
	// TargetData->GetActors().Add(SourceActor->GetController()->GetTargetActor());
	// FGameplayAbilityTargetDataHandle TargetDataHandle;
	// TargetDataHandle.Add(TargetData);
	//
	// FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(AttackDamageEffect);
	// if (EffectSpecHandle.IsValid())
	// {
	// 	ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle, TargetDataHandle);
	// }

	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

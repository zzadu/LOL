// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/Skill/LOLGA_ChangeMontage.h"
#include "LOL.h"
#include "GAS/Character/LOLGASPlayer.h"
#include "Components/MeshComponent.h"
#include "Animation/AnimMontage.h"

ULOLGA_ChangeMontage::ULOLGA_ChangeMontage()
{
	//Super();
}

void ULOLGA_ChangeMontage::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                        const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	ChangeMesh();
}

void ULOLGA_ChangeMontage::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void ULOLGA_ChangeMontage::ChangeMesh()
{
	LOL_LOG(LogLOL, Log, TEXT("ChangeMesh"));

	if (LOLGASPlayer)
	{
		if (isDefault)
		{
			DefaultMontage = LOLGASPlayer->GetCurrentMontage();
			LOLGASPlayer->SetAutoAttackActionMontage(NewMontage);
			
			FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(SkillEffect);
			if (EffectSpecHandle.IsValid())
			{
				// 중첩돼서 더해지지 않도록 수정
				ApplyGameplayEffectSpecToOwner(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle);
			}
			isDefault = false;
		}
		else
		{
			LOLGASPlayer->SetAutoAttackActionMontage(DefaultMontage);
			
			RemoveGrantedByEffect();
			isDefault = true;
		}
	}
}

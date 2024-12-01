// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/Skill/LOLGA_ChangeWeapon.h"
#include "LOL.h"
#include "GAS/Character/LOLGASPlayer.h"
#include "Components/MeshComponent.h"
#include "Animation/AnimMontage.h"

ULOLGA_ChangeWeapon::ULOLGA_ChangeWeapon()
{
	//Super();
}

void ULOLGA_ChangeWeapon::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                        const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (LOLGASPlayer)
	{
		LOLGASPlayer->SetIsDefault(!LOLGASPlayer->GetIsDefault());
		LOLGASPlayer->ChangeAnimation(LOLGASPlayer->GetIsDefault());
	}
	
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void ULOLGA_ChangeWeapon::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
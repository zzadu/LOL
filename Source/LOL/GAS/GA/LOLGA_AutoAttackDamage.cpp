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
	
	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void ULOLGA_AutoAttackDamage::GiveDamage()
{
	UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo_Checked();
	ALOLGASPlayer* SourceActor = Cast<ALOLGASPlayer>(GetActorInfo().AvatarActor.Get());
	ALOLCharacter* TargetActor = SourceActor->GetController()->GetTargetActor();
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	if (!SourceASC || !TargetASC)
	{
		LOL_LOG(LogLOL, Error, TEXT("ASC not found!"));
		return;
	}

	const ULOLCharacterAttributeSet* SourceAttr = SourceASC->GetSet<ULOLCharacterAttributeSet>();
	ULOLCharacterAttributeSet* TargetAttr = const_cast<ULOLCharacterAttributeSet*>(TargetASC->GetSet<ULOLCharacterAttributeSet>());

	if (!SourceAttr || !TargetAttr)
	{
		LOL_LOG(LogLOL, Error, TEXT("Attribute not found!"));
		return;
	}

	const float AttackDamage = SourceAttr->GetAttackRate();
	TargetAttr->SetHealth(TargetAttr->GetHealth() - AttackDamage);
		
}

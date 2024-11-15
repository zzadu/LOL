// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/TA/LOLTA_TraceBase.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"

ALOLTA_TraceBase::ALOLTA_TraceBase()
{
}

void ALOLTA_TraceBase::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);

	SourceActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();
}

void ALOLTA_TraceBase::ConfirmTargetingAndContinue()
{
	if (SourceActor)
	{
		FGameplayAbilityTargetDataHandle DataHandle = MakeTargetData();
		TargetDataReadyDelegate.Broadcast(DataHandle);
	}
}

FGameplayAbilityTargetDataHandle ALOLTA_TraceBase::MakeTargetData() const
{
	return FGameplayAbilityTargetDataHandle();
}

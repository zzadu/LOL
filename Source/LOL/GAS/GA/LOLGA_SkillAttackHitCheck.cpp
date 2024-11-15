// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/LOLGA_SkillAttackHitCheck.h"
#include "LOL.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/GA/AT/LOLAT_Trace.h"
#include "GAS/GA/TA/LOLTA_SingleTarget.h"
#include "GAS/Attribute/LOLCharacterAttributeSet.h"
#include "GAS/Attribute/LOLSkillAttributeSet.h"
#include "Kismet/KismetMathLibrary.h"

ULOLGA_SkillAttackHitCheck::ULOLGA_SkillAttackHitCheck()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void ULOLGA_SkillAttackHitCheck::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	CurrentLevel = TriggerEventData->EventMagnitude;
	
	ULOLAT_Trace* SkillAttackTraceTask = ULOLAT_Trace::CreateTask(this, TargetActorClass);
	SkillAttackTraceTask->OnComplete.AddDynamic(this, &ULOLGA_SkillAttackHitCheck::OnTraceResultCallback);
	SkillAttackTraceTask->ReadyForActivation();
}

void ULOLGA_SkillAttackHitCheck::OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	// 단일 타겟
	if (UAbilitySystemBlueprintLibrary::TargetDataHasHitResult(TargetDataHandle, 0))
	{
		FHitResult HitResult = UAbilitySystemBlueprintLibrary::GetHitResultFromTargetData(TargetDataHandle, 0);
		LOL_LOG(LogLOL, Log, TEXT("Target %s Detected"), *HitResult.GetActor()->GetName());

		UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo_Checked();

		if (!SourceASC)
		{
			LOL_LOG(LogLOL, Error, TEXT("ASC not found!"));
			return;
		}

		const ULOLSkillAttributeSet* SourceAttr = SourceASC->GetSet<ULOLSkillAttributeSet>();

		if (!SourceAttr)
		{
			LOL_LOG(LogLOL, Error, TEXT("Attribute not found!"));
			return;
		}

		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(SkillEffect, CurrentLevel);

		if (isTargeting)
		{
			if (EffectSpecHandle.IsValid())
			{
				float const Distance = FVector::Dist(GetAvatarActorFromActorInfo()->GetActorLocation(), HitResult.GetActor()->GetActorLocation());
				if (Distance < SourceAttr->GetSkillRange())
				{
					FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(GetAvatarActorFromActorInfo()->GetActorLocation(), HitResult.GetActor()->GetActorLocation());
					Rotator.Pitch = 0.0f;
					GetAvatarActorFromActorInfo()->SetActorRotation(Rotator);
			
					ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle, TargetDataHandle);
				}
				else
				{
					LOL_LOG(LogLOL, Error, TEXT("Distance is far"));
				}
			}
		}
		else
		{
			if (EffectSpecHandle.IsValid())
			{
				//EffectSpecHandle.Data->SetSetByCallerMagnitude(ABTAG_DATA_DAMAGE, -SourceAttribute->GetAttackRate());
				ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle, TargetDataHandle);
		
				FGameplayEffectContextHandle CueContextHandle = UAbilitySystemBlueprintLibrary::GetEffectContext(EffectSpecHandle);
				CueContextHandle.AddHitResult(HitResult);
				FGameplayCueParameters CueParam;
				CueParam.EffectContext = CueContextHandle;

				//TargetASC->ExecuteGameplayCue(ABTAG_GAMEPLAYCUE_CHARACTER_ATTACKHIT, CueParam);
			}
		}
		
	}
	// 다중 타겟
	else if (UAbilitySystemBlueprintLibrary::TargetDataHasActor(TargetDataHandle, 0))
	{
		UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo_Checked();
		//FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(SkillEffect, CurrentLevel);
		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(SkillEffect);
		if (EffectSpecHandle.IsValid())
		{
			//EffectSpecHandle.Data->SetSetByCallerMagnitude(ABTAG_DATA_DAMAGE, -SourceAttribute->GetAttackRate());
			ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle, TargetDataHandle);

			FGameplayEffectContextHandle CueContextHandle = UAbilitySystemBlueprintLibrary::GetEffectContext(EffectSpecHandle);
			CueContextHandle.AddActors(TargetDataHandle.Data[0].Get()->GetActors(), false);
			FGameplayCueParameters CueParam;
			CueParam.EffectContext = CueContextHandle;

			//SourceASC->ExecuteGameplayCue(ABTAG_GAMEPLAYCUE_CHARACTER_ATTACKHIT, CueParam);
		}
	}

	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

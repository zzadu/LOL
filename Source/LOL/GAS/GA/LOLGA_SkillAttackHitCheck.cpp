// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/LOLGA_SkillAttackHitCheck.h"
#include "LOL.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/GA/AT/LOLAT_Trace.h"
#include "GAS/GA/TA/LOLTA_Trace.h"
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

	if (isTargeting && !isMultiTargeting)
	{
		ULOLAT_Trace* SkillAttackTraceTask = ULOLAT_Trace::CreateTask(this, ALOLTA_Trace::StaticClass(), isTargeting, isMultiTargeting);
		SkillAttackTraceTask->OnComplete.AddDynamic(this, &ULOLGA_SkillAttackHitCheck::OnTraceResultCallback);
		SkillAttackTraceTask->ReadyForActivation();
	}
}

void ULOLGA_SkillAttackHitCheck::OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	if (UAbilitySystemBlueprintLibrary::TargetDataHasHitResult(TargetDataHandle, 0))
	{
		FHitResult HitResult = UAbilitySystemBlueprintLibrary::GetHitResultFromTargetData(TargetDataHandle, 0);
		LOL_LOG(LogLOL, Log, TEXT("Target %s Detected"), *HitResult.GetActor()->GetName());

		UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo_Checked();
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitResult.GetActor());

		if (!SourceASC || !TargetASC)
		{
			LOL_LOG(LogLOL, Error, TEXT("ASC not found!"));
			return;
		}

		const ULOLSkillAttributeSet* SourceAttr = SourceASC->GetSet<ULOLSkillAttributeSet>();
		ULOLCharacterAttributeSet* TargetAttr = const_cast<ULOLCharacterAttributeSet*>(TargetASC->GetSet<ULOLCharacterAttributeSet>());

		if (!SourceAttr || !TargetAttr)
		{
			LOL_LOG(LogLOL, Error, TEXT("Attribute not found!"));
			return;
		}

		float const Distance = FVector::Dist(GetAvatarActorFromActorInfo()->GetActorLocation(), HitResult.GetActor()->GetActorLocation());
		if (Distance < SourceAttr->GetSkillRange())
		{
			FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(GetAvatarActorFromActorInfo()->GetActorLocation(), HitResult.GetActor()->GetActorLocation());
			Rotator.Pitch = 0.0f;
			GetAvatarActorFromActorInfo()->SetActorRotation(Rotator);
			
			const float AttackDamage = SourceAttr->GetSkillAttackDamage();
			TargetAttr->SetHealth(TargetAttr->GetHealth() - AttackDamage);
		}
		else
		{
			LOL_LOG(LogLOL, Error, TEXT("Distance is far"));
		}
		
	}

	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

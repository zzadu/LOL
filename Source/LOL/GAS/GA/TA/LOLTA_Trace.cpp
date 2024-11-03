// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/TA/LOLTA_Trace.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Physics/LOLCollision.h"
#include "DrawDebugHelpers.h"

ALOLTA_Trace::ALOLTA_Trace()
{
}

void ALOLTA_Trace::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);

	SourceActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();
}

void ALOLTA_Trace::ConfirmTargetingAndContinue()
{
	if (SourceActor)
	{
		FGameplayAbilityTargetDataHandle DataHandle = MakeTargetData();
		TargetDataReadyDelegate.Broadcast(DataHandle);
	}
}

FGameplayAbilityTargetDataHandle ALOLTA_Trace::MakeTargetData() const
{
	// 타겟팅, 단일 타겟 스킬
	ACharacter* Character = CastChecked<ACharacter>(SourceActor);

	FHitResult OutHitResult;
	const float AttackRange = 500.0f;
	const float AttackRadius = 50.0f;

	// 플레이어가 바라보는 방향이 아니라 마우스 시작으로 탐지하는 걸로 바꿔야 함
	FCollisionQueryParams Params(SCENE_QUERY_STAT(ULOLTA_Trace), false, Character);
	const FVector Forward = Character->GetActorForwardVector();
	const FVector Start = Character->GetActorLocation() + Forward * Character->GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + Forward * AttackRange;
	
	bool HitDetected = GetWorld()->LineTraceSingleByChannel(OutHitResult, Start, End, CCHANNEL_ABACTION, Params);

	FGameplayAbilityTargetDataHandle DataHandle;
	if (HitDetected)
	{
		FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit(OutHitResult);
		DataHandle.Add(TargetData);
	}

#if ENABLE_DRAW_DEBUG
	if (bShowDebug)
	{
		FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;
		DrawDebugLine(GetWorld(), Start, End, DrawColor, false, 5.0f);
	}
#endif

	return DataHandle;
}

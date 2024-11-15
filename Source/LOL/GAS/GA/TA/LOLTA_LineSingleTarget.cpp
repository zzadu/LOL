// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/TA/LOLTA_LineSingleTarget.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "LOL.h"
#include "Character/LOLPlayer.h"
#include "GameFramework/Character.h"
#include "GAS/Attribute/LOLSkillAttributeSet.h"
#include "Physics/LOLCollision.h"
#include "Player/LOLPlayerController.h"
#include "Components/CapsuleComponent.h"

ALOLTA_LineSingleTarget::ALOLTA_LineSingleTarget()
{
}

FGameplayAbilityTargetDataHandle ALOLTA_LineSingleTarget::MakeTargetData() const
{
	ACharacter* Character = CastChecked<ACharacter>(SourceActor);

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);
	if (!ASC)
	{
		LOL_LOG(LogLOL, Error, TEXT("ASC not found!"));
		return FGameplayAbilityTargetDataHandle();
	}

	const ULOLSkillAttributeSet* AttributeSet = ASC->GetSet<ULOLSkillAttributeSet>();
	if (!AttributeSet)
	{
		LOL_LOG(LogLOL, Error, TEXT("LOLSkillAttributeSet not found!"));
		return FGameplayAbilityTargetDataHandle();
	}
	
	FHitResult OutHitResult;

	FCollisionQueryParams Params(SCENE_QUERY_STAT(ALOLTA_LineSingleTarget), false, Character);

	ALOLPlayerController* PC = Cast<ALOLPlayer>(SourceActor)->GetController();
	if (!PC)
	{
		LOL_LOG(LogLOL, Error, TEXT("LOLPlayerController not found!"));
		return FGameplayAbilityTargetDataHandle();
	}

	FVector MouseVector, MouseDirection;
	PC->DeprojectMousePositionToWorld(MouseVector, MouseDirection);
	const FVector Forward = Character->GetActorForwardVector();
	const FVector Start = Character->GetActorLocation() + Forward * Character->GetCapsuleComponent()->GetScaledCapsuleRadius();
	FVector End = MouseVector + MouseDirection * AttributeSet->GetSkillRange();
	
	bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, CCHANNEL_LOLACTION, FCollisionShape::MakeSphere(AttributeSet->GetSkillRadius()), Params);
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
		DrawDebugLine(GetWorld(), Start, End, DrawColor, true, 5.0f);
	}
#endif

	return DataHandle;
}

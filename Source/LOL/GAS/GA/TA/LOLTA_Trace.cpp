// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/TA/LOLTA_Trace.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Physics/LOLCollision.h"
#include "DrawDebugHelpers.h"
#include "AbilitySystemComponent.h"
#include "GAS/Attribute/LOLCharacterAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "InteractiveToolManager.h"
#include "LOL.h"
#include "Character/LOLCharacter.h"
#include "Character/LOLPlayer.h"
#include "GAS/Attribute/LOLSkillAttributeSet.h"
#include "Player/LOLPlayerController.h"

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

	FCollisionQueryParams Params(SCENE_QUERY_STAT(ULOLTA_Trace), false, Character);

	ALOLPlayerController* PC = Cast<ALOLPlayer>(SourceActor)->GetController();
	if (!PC)
	{
		LOL_LOG(LogLOL, Error, TEXT("LOLPlayerController not found!"));
		return FGameplayAbilityTargetDataHandle();
	}

	FVector MouseVector, MouseDirection;
	PC->DeprojectMousePositionToWorld(MouseVector, MouseDirection);
	FVector End = MouseVector + MouseDirection * 1000.f;
	
	bool HitDetected = GetWorld()->LineTraceSingleByChannel(OutHitResult, MouseVector, End, CCHANNEL_ABACTION, Params);

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
		DrawDebugLine(GetWorld(), MouseVector, End, DrawColor, true, 5.0f);
	}
#endif

	return DataHandle;
}

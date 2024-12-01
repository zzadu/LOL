// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/LOLAnimInstance.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/Attribute/LOLCharacterAttributeSet.h"
#include "GAS/Character/LOLGASPlayer.h"

ULOLAnimInstance::ULOLAnimInstance()
{
}

void ULOLAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ALOLGASPlayer>(GetOwningActor());
}

void ULOLAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// if (!Owner->ActorHasTag(FName("Character.State.IsMoving")))
	// {
	// 	bIsIdle = true;
	// }
}

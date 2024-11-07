// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/LOLGA_Move.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_MoveToLocation.h"
#include "LOL.h"
#include "Character/LOLPlayer.h"
#include "GAS/Attribute/LOLCharacterAttributeSet.h"
#include "Player/LOLPlayerController.h"
#include "GameplayTagContainer.h"

ULOLGA_Move::ULOLGA_Move()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void ULOLGA_Move::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	LOL_LOG(LogLOL, Log, TEXT("Begin"));

	ALOLPlayerController* PC = Cast<ALOLPlayer>(ActorInfo->AvatarActor.Get())->GetController();
	if (!PC)
	{
		LOL_LOG(LogLOL, Error, TEXT("LOLPlayerController not found!"));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}

	FHitResult Hit;
	bool bHitSuccessful = PC->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, OUT Hit);

	if (bHitSuccessful)
	{
		if (ALOLCharacter* TargetActor = Cast<ALOLCharacter>(Hit.GetActor()))
		{
			PC->SetTargetActor(TargetActor);
				
			UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo_Checked();
			UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
			
			if (!SourceASC || !TargetASC)
			{
				LOL_LOG(LogLOL, Error, TEXT("AbilitySystemComponent not found!"));
			}
			
			CachedLocation = TargetActor->GetActorLocation();
		}
		else
		{
			PC->SetTargetActor(nullptr);
			
			CachedLocation = Hit.Location;
		}
	}

	CachedLocation.Z = ActorInfo->AvatarActor.Get()->GetActorLocation().Z;
	PC->LookAt(CachedLocation);
	LOL_LOG(LogLOL, Log, TEXT("%f %f"), CachedLocation.X, CachedLocation.Y);
	UAbilityTask_MoveToLocation* MoveToLocation = UAbilityTask_MoveToLocation::MoveToLocation(this, TEXT("MoveToLcation"), CachedLocation, 1.0f, nullptr, nullptr);
	MoveToLocation->OnTargetLocationReached.AddDynamic(this, &ULOLGA_Move::OnCompleteCallback);
	MoveToLocation->ReadyForActivation();
}

void ULOLGA_Move::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void ULOLGA_Move::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	LOL_LOG(LogLOL, Log, TEXT("End"));
}

void ULOLGA_Move::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	//Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	
	if (ActivationOwnedTags.HasTag(FGameplayTag::RequestGameplayTag(FName("Character.State.IsMoving"))))
	{
		//CancelTaskByInstanceName(TEXT("MoveToLcation"));
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}
}

void ULOLGA_Move::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	ALOLPlayerController* PC = Cast<ALOLPlayer>(ActorInfo->AvatarActor.Get())->GetController();
	if (!PC)
	{
		LOL_LOG(LogLOL, Error, TEXT("LOLPlayerController not found!"));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}
	
	
	CancelAbility(Handle, ActorInfo, ActivationInfo, true);
}

void ULOLGA_Move::OnCompleteCallback()
{
	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

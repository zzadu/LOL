// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA/AT/LOLAT_Trace.h"
#include "GAS/GA/TA/LOLTA_Trace.h"
#include "AbilitySystemComponent.h"

ULOLAT_Trace::ULOLAT_Trace()
{
}

ULOLAT_Trace* ULOLAT_Trace::CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<ALOLTA_Trace> TargetActorClass, bool isTargeting, bool isMultiTargeting)
{
	ULOLAT_Trace* NewTask = NewAbilityTask<ULOLAT_Trace>(OwningAbility);

	NewTask->isTargeting = isTargeting;
	NewTask->isMultiTargeting = isMultiTargeting;
	NewTask->TargetActorClass = TargetActorClass;
	return NewTask;
}

void ULOLAT_Trace::Activate()
{
	Super::Activate();

	SpawnAndInitializeTargetActor();
	FinalizeTargetActor();
	
	SetWaitingOnAvatar();
}

void ULOLAT_Trace::OnDestroy(bool bInOwnerFinished)
{
	if (SpawnedTargetActor)
	{
		SpawnedTargetActor->Destroy();
	}
	
	Super::OnDestroy(bInOwnerFinished);
}

void ULOLAT_Trace::SpawnAndInitializeTargetActor()
{
	if (isTargeting && !isMultiTargeting)
	{
		// 타겟팅, 단일 타겟팅
		SpawnedTargetActor = Cast<ALOLTA_Trace>(Ability->GetWorld()->SpawnActorDeferred<AGameplayAbilityTargetActor>(TargetActorClass, FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn));

		if (SpawnedTargetActor)
		{
			SpawnedTargetActor->SetShowDebug(true);
			SpawnedTargetActor->TargetDataReadyDelegate.AddUObject(this, &ULOLAT_Trace::OnTargetDataReadyCallback);
		}
	}
}

void ULOLAT_Trace::FinalizeTargetActor()
{
	UAbilitySystemComponent* ASC = AbilitySystemComponent.Get();

	if (ASC)
	{
		const FTransform SpawnTransform = ASC->GetAvatarActor()->GetTransform();
		SpawnedTargetActor->FinishSpawning(SpawnTransform);

		ASC->SpawnedTargetActors.Push(SpawnedTargetActor);
		SpawnedTargetActor->StartTargeting(Ability);
		SpawnedTargetActor->ConfirmTargeting();
	}
}

void ULOLAT_Trace::OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& DataHandle)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnComplete.Broadcast(DataHandle);
	}

	// GA에게 타겟 정보 넘겨줌

	EndTask();
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "LOLAT_Trace.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTraceResultDelegate, const FGameplayAbilityTargetDataHandle&, TargetDataHandle);

/**
 * 
 */
UCLASS()
class LOL_API ULOLAT_Trace : public UAbilityTask
{
	GENERATED_BODY()

public:
	ULOLAT_Trace();

	UFUNCTION(BlueprintCallable, Category = "Ability/Tasks", meta = (DisplayName = "WaitForTrace", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static ULOLAT_Trace* CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<class AGameplayAbilityTargetActor> TargetActorClass);

	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

	void SpawnAndInitializeTargetActor();
	void FinalizeTargetActor();

protected:
	void OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& DataHandle);

public:
	UPROPERTY(BlueprintAssignable)
	FTraceResultDelegate OnComplete;

protected:
	UPROPERTY()
	TSubclassOf<class ALOLTA_TraceBase> TargetActorClass;

	UPROPERTY()
	TObjectPtr<ALOLTA_TraceBase> SpawnedTargetActor;
	
};

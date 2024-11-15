// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagsManager.h"
#include "AnimNotify_GASAttack.generated.h"

/**
 * 
 */
UCLASS()
class LOL_API UAnimNotify_GASAttack : public UAnimNotify
{
	GENERATED_BODY()

public:
	UAnimNotify_GASAttack();

protected:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere, meta=(Categories=Event))
	FGameplayTag TriggerGameplayTag;
};

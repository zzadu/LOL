// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Animation/AnimNotify_GASAttack.h"
#include "AbilitySystemBlueprintLibrary.h"

UAnimNotify_GASAttack::UAnimNotify_GASAttack()
{
}

FString UAnimNotify_GASAttack::GetNotifyName_Implementation() const
{
	return TEXT("GASAttack");
}

void UAnimNotify_GASAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		AActor* OwnerActor = MeshComp->GetOwner();

		if (OwnerActor)
		{
			FGameplayEventData PayloadData;
			int32 level = FCString::Atoi(*Animation->GetName());
			PayloadData.EventMagnitude = level;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, TriggerGameplayTag, PayloadData);
		}
	}
	
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LOLGASUserWidget.h"
#include "AbilitySystemBlueprintLibrary.h"


void ULOLGASUserWidget::SetAbilitySystemComponent(AActor* InOwner)
{
	if (IsValid(InOwner))
	{
		ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InOwner);
	}
}

UAbilitySystemComponent* ULOLGASUserWidget::GetAbilitySystemComponent() const
{
	return ASC;
}

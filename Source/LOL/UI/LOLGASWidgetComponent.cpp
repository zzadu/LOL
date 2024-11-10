// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LOLGASWidgetComponent.h"
#include "UI/LOLGASUserWidget.h"

ULOLGASWidgetComponent::ULOLGASWidgetComponent()
{
}

void ULOLGASWidgetComponent::InitWidget()
{
	Super::InitWidget();

	ULOLGASUserWidget* GASUserWidget = Cast<ULOLGASUserWidget>(GetWidget());
	if (GASUserWidget)
	{
		GASUserWidget->SetAbilitySystemComponent(GetOwner());
	}
}

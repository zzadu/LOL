// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LOLGASHpBarUserWidget.h"
#include "AbilitySystemComponent.h"
#include "GAS/Attribute/LOLCharacterAttributeSet.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

ULOLGASHpBarUserWidget::ULOLGASHpBarUserWidget()
{
}

void ULOLGASHpBarUserWidget::SetAbilitySystemComponent(AActor* InOwner)
{
	Super::SetAbilitySystemComponent(InOwner);

	if (ASC)
	{
		ASC->GetGameplayAttributeValueChangeDelegate(ULOLCharacterAttributeSet::GetHealthAttribute()).AddUObject(this, &ULOLGASHpBarUserWidget::OnHealthChanced);
		ASC->GetGameplayAttributeValueChangeDelegate(ULOLCharacterAttributeSet::GetMaxHealthAttribute()).AddUObject(this, &ULOLGASHpBarUserWidget::OnMaxHealthChanced);

		const ULOLCharacterAttributeSet* CurrentAttributeSet = ASC->GetSet<ULOLCharacterAttributeSet>();
		if (CurrentAttributeSet)
		{
			CurrentHealth = CurrentAttributeSet->GetHealth();
			CurrentMaxHealth = CurrentAttributeSet->GetMaxHealth();
			UpdateHpBar();

		}
	}
}

void ULOLGASHpBarUserWidget::OnHealthChanced(const FOnAttributeChangeData& ChangeData)
{
	CurrentHealth = ChangeData.NewValue;
	UpdateHpBar();
}

void ULOLGASHpBarUserWidget::OnMaxHealthChanced(const FOnAttributeChangeData& ChangeData)
{
	CurrentMaxHealth = ChangeData.NewValue;
	UpdateHpBar();
}

void ULOLGASHpBarUserWidget::UpdateHpBar()
{
	if (PbHpBar)
	{
		PbHpBar->SetPercent(CurrentHealth / CurrentMaxHealth);
	}

	if (TxtHpStat)
	{
		TxtHpStat->SetText(FText::FromString(FString::Printf(TEXT("%.0f/%0.f"), CurrentHealth, CurrentMaxHealth)));
	}
}

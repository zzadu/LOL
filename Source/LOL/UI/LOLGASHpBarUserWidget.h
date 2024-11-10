// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Attribute/LOLCharacterAttributeSet.h"
#include "UI/LOLGASUserWidget.h"
#include "LOLGASHpBarUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOL_API ULOLGASHpBarUserWidget : public ULOLGASUserWidget
{
	GENERATED_BODY()

public:
	ULOLGASHpBarUserWidget();

protected:
	virtual void SetAbilitySystemComponent(AActor* InOwner) override;

	virtual void OnHealthChanced(const FOnAttributeChangeData& ChangeData);
	virtual void OnMaxHealthChanced(const FOnAttributeChangeData& ChangeData);

	void UpdateHpBar();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> PbHpBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TxtHpStat;
	
	float CurrentHealth = 0.0f;
	float CurrentMaxHealth = 0.1f;
};

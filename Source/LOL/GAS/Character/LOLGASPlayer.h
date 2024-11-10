// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LOLPlayer.h"
#include "AbilitySystemInterface.h"
#include "LOLGASPlayer.generated.h"

/**
 * 
 */
UCLASS()
class LOL_API ALOLGASPlayer : public ALOLPlayer, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ALOLGASPlayer();

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void LearnSkill(int32 InputId);

protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY(EditAnywhere, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;

	UPROPERTY(EditAnywhere, Category = GAS)
	TMap<int32, TSubclassOf<class UGameplayAbility>> StartInputAbilities;

	UPROPERTY(EditAnywhere, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> SkillAbilities;

public:
	FORCEINLINE virtual class UAnimMontage* GetSkillActionMontage(int32 InputId) const { return SkillActionMontages[InputId]; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GAS)
	TArray<TObjectPtr<class UAnimMontage>> SkillActionMontages;

	// widget
	UPROPERTY(VisibleAnywhere);
	TObjectPtr<class ULOLGASWidgetComponent> HpBar;
};

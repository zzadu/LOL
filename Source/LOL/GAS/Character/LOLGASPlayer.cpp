// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Character/LOLGASPlayer.h"
#include "AbilitySystemComponent.h"
#include "GAS/Player/LOLGASPlayerState.h"
#include "Player/LOLPlayerController.h"

ALOLGASPlayer::ALOLGASPlayer()
{
	ASC = nullptr;
}

void ALOLGASPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ALOLGASPlayerState* GASPS = GetPlayerState<ALOLGASPlayerState>();
	if (GASPS)
	{
		ASC = GASPS->GetAbilitySystemComponent();
		ASC->InitAbilityActorInfo(GASPS, this);

		for (const auto& StartAbility : StartInputAbilities)
		{
			FGameplayAbilitySpec StartSpec(StartAbility.Value);
			StartSpec.InputID = StartAbility.Key;
			ASC->GiveAbility(StartSpec);
			std::cout << StartSpec.Level;
		}

		int32 InputId = 0;
		for (const auto& SkillAbility : SkillAbilities)
		{
			FGameplayAbilitySpec StartSpec(SkillAbility);
			StartSpec.InputID = InputId++;
			ASC->GiveAbility(StartSpec);
			std::cout << StartSpec.Level;
		}
		
		LOLPlayerController->SetupGASInputComponent();
	}
}

void ALOLGASPlayer::SetupPlayerInputComponent(class UInputComponent* inputComponent)
{
	Super::SetupPlayerInputComponent(inputComponent);

	//LOLPlayerController->SetupGASInputComponent();
}


UAbilitySystemComponent* ALOLGASPlayer::GetAbilitySystemComponent() const
{
	return ASC;
}

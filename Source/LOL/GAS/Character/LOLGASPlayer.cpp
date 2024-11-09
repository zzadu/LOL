// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Character/LOLGASPlayer.h"
#include "AbilitySystemComponent.h"
#include "GAS/Player/LOLGASPlayerState.h"
#include "Player/LOLPlayerController.h"
#include "LOL.h"

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

		for (const auto& StartAbility : StartAbilities)
		{
			FGameplayAbilitySpec StartSpec(StartAbility);
			ASC->GiveAbility(StartSpec);
		}

		for (const auto& StartInputAbility : StartInputAbilities)
		{
			FGameplayAbilitySpec StartSpec(StartInputAbility.Value);
			StartSpec.InputID = StartInputAbility.Key;
			ASC->GiveAbility(StartSpec);
		}
		
		LOLPlayerController->SetupGASInputComponent();
	}
}

void ALOLGASPlayer::SetupPlayerInputComponent(class UInputComponent* inputComponent)
{
	Super::SetupPlayerInputComponent(inputComponent);

	//LOLPlayerController->SetupGASInputComponent();
}

void ALOLGASPlayer::LearnSkill(int32 InputId)
{
	if (FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(InputId))
	{
		Spec->Level++;
		
		LOL_LOG(LogLOL, Log, TEXT("Current Skill %d Level: %d"), InputId, Spec->Level);
	}
	else {
		FGameplayAbilitySpec AbilitySpec(*SkillAbilities[InputId], 1);
		AbilitySpec.InputID = InputId;
		FGameplayAbilitySpecHandle SpecHandle = ASC->GiveAbility(AbilitySpec);

		LOL_LOG(LogLOL, Log, TEXT("Current Skill %d Level: %d"), InputId, AbilitySpec.Level);

		//SpecHandles.Add(SpecHandle);
	}
}


UAbilitySystemComponent* ALOLGASPlayer::GetAbilitySystemComponent() const
{
	return ASC;
}

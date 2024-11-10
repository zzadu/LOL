// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Character/LOLGASPlayer.h"
#include "AbilitySystemComponent.h"
#include "GAS/Player/LOLGASPlayerState.h"
#include "Player/LOLPlayerController.h"
#include "LOL.h"
#include "UI/LOLGASWidgetComponent.h"
#include "UI/LOLGASUserWidget.h"

ALOLGASPlayer::ALOLGASPlayer()
{
	ASC = nullptr;

	HpBar = CreateDefaultSubobject<ULOLGASWidgetComponent>(TEXT("Widget"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0, 0, 180.f));

	static ConstructorHelpers::FClassFinder<UUserWidget> HpBarWidgetRef(TEXT("/Game/UI/WBP_HpBar.WBP_HpBar_C"));
	if (HpBarWidgetRef.Class)
	{
		HpBar->SetWidgetClass(HpBarWidgetRef.Class);
		HpBar->SetWidgetSpace(EWidgetSpace::Screen);
		HpBar->SetDrawSize(FVector2D(200.0f, 20.f));
		HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
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

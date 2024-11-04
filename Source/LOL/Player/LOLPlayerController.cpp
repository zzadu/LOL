// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LOLPlayerController.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "LOL.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Character/LOLPlayer.h"
#include "GAS/Attribute/LOLCharacterAttributeSet.h"
#include "GAS/Character/LOLGASPlayer.h"
#include "Kismet/KismetMathLibrary.h"


class ULOLCharacterAttributeSet;

ALOLPlayerController::ALOLPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	TargetActor = nullptr;
}

void ALOLPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	SetupInputMappingContext();

}

void ALOLPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (TargetActor)
	{
		if (CanAttack())
		{
			StopMovement();
			AutoAttack();
		}
		else
		{
			UAIBlueprintHelperLibrary::SimpleMoveToActor(this, TargetActor);
		}
	}
}

void ALOLPlayerController::SetupInputMappingContext()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (InputMappingContext)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void ALOLPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &ALOLPlayerController::Move);
	
}

void ALOLPlayerController::SetupGASInputComponent()
{
	LOLPlayer = Cast<ALOLGASPlayer>(GetCharacter());
	ASC = LOLPlayer->GetAbilitySystemComponent();
	if (IsValid(ASC) && IsValid(InputComponent))
	{
		UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

		EnhancedInputComponent->BindAction(SkillAction, ETriggerEvent::Triggered, this, &ALOLPlayerController::GASInputPressed, 0);
		EnhancedInputComponent->BindAction(SkillAction, ETriggerEvent::Completed, this, &ALOLPlayerController::GASInputReleased, 0);

		AttributeSet = ASC->GetSet<ULOLCharacterAttributeSet>();
	}
}

ALOLCharacter* ALOLPlayerController::GetTargetActor()
{
	return TargetActor;
}

void ALOLPlayerController::Move()
{
	FHitResult Hit;
	bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, OUT Hit);

	if (bHitSuccessful)
	{
		FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(LOLPlayer->GetActorLocation(), Hit.Location);
		Rotator.Pitch = 0.0f;
		LOLPlayer->SetActorRotation(Rotator);
		
		TargetActor = Cast<ALOLCharacter>(Hit.GetActor());
		if (!TargetActor)
		{
			EndAutoAttack();
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Hit.Location);
		}
	}
}

bool ALOLPlayerController::CanAttack()
{
	float const Distance = FVector::Dist(TargetActor->GetActorLocation(), LOLPlayer->GetActorLocation());

	if (!AttributeSet)
	{
		LOL_LOG(LogLOL, Error, TEXT("LOLCharacterAttributeSet not found!"));
		return false;
	}
	
	if (Distance <= AttributeSet->GetAttackRange())
	{
		return true;
	}

	return false;
}

void ALOLPlayerController::AutoAttack()
{
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(10);
	if (Spec)
	{
			if (Spec->Level != 0)
			{
				ASC->TryActivateAbility(Spec->Handle);
			}
	}
}

void ALOLPlayerController::EndAutoAttack()
{
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(10);
	if (Spec)
	{
		ASC->CancelAbility(Spec->Ability);
	}
}

void ALOLPlayerController::GASInputPressed(int32 InputId)
{
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(InputId);
	if (Spec)
	{
		Spec->InputPressed = true;
		if (Spec->IsActive())
		{
			ASC->AbilitySpecInputPressed(*Spec);
		}
		else
		{
			if (Spec->Level != 0)
			{
				ASC->TryActivateAbility(Spec->Handle);
			}
		}
	}
}

void ALOLPlayerController::GASInputReleased(int32 InputId)
{
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(InputId);
	if (Spec)
	{
		Spec->InputPressed = false;
		if (Spec->IsActive())
		{
			ASC->AbilitySpecInputReleased(*Spec);
		}
	}
}


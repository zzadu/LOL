// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LOLPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Character/LOLPlayer.h"
#include "Kismet/KismetMathLibrary.h"


ALOLPlayerController::ALOLPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ALOLPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	SetupInputMappingContext();
	LOLPlayer = Cast<ALOLPlayer>(GetCharacter());
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

void ALOLPlayerController::Move()
{
	FHitResult Hit;
	bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, OUT Hit);

	if (bHitSuccessful)
	{
		ALOLPlayer* TargetActor = Cast<ALOLPlayer>(Hit.GetActor());
		if (TargetActor)
		{
			FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(LOLPlayer->GetActorLocation(), TargetActor->GetActorLocation());
			LOLPlayer->SetActorRotation(Rotator);
			Attack(Hit.GetActor());
		}
		else
		{
			FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(LOLPlayer->GetActorLocation(), Hit.Location);
			LOLPlayer->SetActorRotation(Rotator);
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Hit.Location);
		}
	}
}

void ALOLPlayerController::Attack(class AActor* Target)
{
	
	if (LOLPlayer)
	{
		float const Distance = FVector::Dist(Target->GetActorLocation(), LOLPlayer->GetActorLocation());
		if (Distance < 100.f)
		{
			StopMovement();
			// 공격 effect
		}
		else
		{
			UAIBlueprintHelperLibrary::SimpleMoveToActor(this, Target);
		}
	}
}


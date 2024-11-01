// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LOLPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Player/LOLPlayerController.h"



ALOLPlayer::ALOLPlayer()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->SetUsingAbsoluteRotation(true);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	SpringArm->TargetArmLength = 800.f;
	SpringArm->SetRelativeRotation(FRotator(-60, 0, 0));
	
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, 180.f, 0.f));

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// HpBar = CreateDefaultSubobject<ULOLWidgetComponent>(TEXT("Widget"));
	// HpBar->SetupAttachment(GetMesh());
	// HpBar->SetRelativeLocation(FVector(0, 0, 180.f));
	//
	// static ConstructorHelpers::FClassFinder<UUserWidget> HpBarWidgetRef(TEXT("/Game/UI/WB_HpBar.WB_HpBar_C"));
	// if (HpBarWidgetRef.Class)
	// {
	// 	HpBar->SetWidgetClass(HpBarWidgetRef.Class);
	// 	HpBar->SetWidgetSpace(EWidgetSpace::Screen);
	// 	HpBar->SetDrawSize(FVector2D(200.0f, 20.f));
	// 	HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// }
}

void ALOLPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	

	APlayerController* PlayerController = CastChecked<APlayerController>(NewController);
	PlayerController->ConsoleCommand(TEXT("showdebug abilitysystem"));

	LOLPlayerController = Cast<ALOLPlayerController>(PlayerController);
	LOLPlayerController->SetupInputComponent();

}

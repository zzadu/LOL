// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LOLCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Physics/LOLCollision.h"

// Sets default values
ALOLCharacter::ALOLCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_LOLCAPSULE);

	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void ALOLCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALOLCharacter::SetDead()
{
}

void ALOLCharacter::PlayDeadAnimation()
{
}


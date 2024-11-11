// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Character/LOLGASMonster.h"
#include "AbilitySystemComponent.h"
#include "GAS/Attribute/LOLCharacterAttributeSet.h"
#include "UI/LOLGASWidgetComponent.h"
#include "UI/LOLGASUserWidget.h"

ALOLGASMonster::ALOLGASMonster()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	AttributeSet = CreateDefaultSubobject<ULOLCharacterAttributeSet>(TEXT("CharacterAttributeSet"));

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

class UAbilitySystemComponent* ALOLGASMonster::GetAbilitySystemComponent() const
{
	return ASC;
}


void ALOLGASMonster::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ASC->InitAbilityActorInfo(this, this);
	AttributeSet->OnOutOfHealth.AddDynamic(this, &ALOLGASMonster::OnOutOfHealth);
}

void ALOLGASMonster::OnOutOfHealth()
{
	SetDead();
}

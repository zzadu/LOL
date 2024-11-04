// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Player/LOLGASPlayerState.h"
#include "AbilitySystemComponent.h"
#include "GAS/Attribute/LOLCharacterAttributeSet.h"
#include "GAS/Attribute/LOLSkillAttributeSet.h"

ALOLGASPlayerState::ALOLGASPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	AttributeSet = CreateDefaultSubobject<ULOLCharacterAttributeSet>(TEXT("CharacterAttributeSet"));
	SkillSet.Add(CreateDefaultSubobject<ULOLSkillAttributeSet>(TEXT("SkillAttributeSet")));

	// 서버에서 클라이언트로 전송하기 위함
	//ASC->SetIsReplicated(true);
}

class UAbilitySystemComponent* ALOLGASPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}

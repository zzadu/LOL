// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Player/LOLGASPlayerState.h"
#include "AbilitySystemComponent.h"

ALOLGASPlayerState::ALOLGASPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));

	// 서버에서 클라이언트로 전송하기 위함
	//ASC->SetIsReplicated(true);
}

class UAbilitySystemComponent* ALOLGASPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}

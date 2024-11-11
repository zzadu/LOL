#pragma once

#include "GameplayTagContainer.h"

#define LOLTAG_CHARACTER_ISDEAD FGameplayTag::RequestGameplayTag(FName("Character.State.IsDead"))
#define LOLTAG_CHARACTER_INVINCIBLE FGameplayTag::RequestGameplayTag(FName("Character.State.Invincible"))
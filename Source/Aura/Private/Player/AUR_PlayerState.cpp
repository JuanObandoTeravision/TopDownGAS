// Copyright Teravision Games


#include "Player/AUR_PlayerState.h"

#include "AUR_AttributeSet.h"
#include "AbilitySystem/AUR_AbilitySystemComponent.h"

AAUR_PlayerState::AAUR_PlayerState()
{
	NetUpdateFrequency = 100.0f;

	AbilitySystemComponent = CreateDefaultSubobject<UAUR_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UAUR_AttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AAUR_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

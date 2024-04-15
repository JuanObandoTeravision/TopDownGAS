// Copyright Teravision Games


#include "Player/AUR_PlayerState.h"

#include "AUR_AttributeSet.h"
#include "AbilitySystem/AUR_AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

AAUR_PlayerState::AAUR_PlayerState()
{
	NetUpdateFrequency = 100.0f;

	AbilitySystemComponent = CreateDefaultSubobject<UAUR_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UAUR_AttributeSet>("AttributeSet");
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

void AAUR_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAUR_PlayerState, Level);Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

UAbilitySystemComponent* AAUR_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAUR_PlayerState::OnRep_Level(int32 OldLevel)
{
}

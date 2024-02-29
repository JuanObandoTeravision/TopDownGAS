// Copyright Teravision Games


#include "AUR_AttributeSet.h"

#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

UAUR_AttributeSet::UAUR_AttributeSet()
{
	InitHealth(75.f);
	InitMaxHealth(100.f);
	InitMana(75.f);
	InitMaxMana(100.f);
}

void UAUR_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAUR_AttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAUR_AttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAUR_AttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAUR_AttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UAUR_AttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAUR_AttributeSet, Health, OldHealth);
}

void UAUR_AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAUR_AttributeSet, MaxHealth, OldMaxHealth);
}

void UAUR_AttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAUR_AttributeSet, Mana, OldMana);
}

void UAUR_AttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAUR_AttributeSet, MaxMana, OldMaxMana);
}

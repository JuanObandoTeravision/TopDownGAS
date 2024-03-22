// Copyright Teravision Games


#include "AbilitySystem/AUR_AbilitySystemComponent.h"
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AbilitySystemComponent::OnAbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAUR_AbilitySystemComponent::EffectApplied);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	GEngine->AddOnScreenDebugMessage(1, 8.f, FColor::Blue, FString("Effect Applied!"));
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Copyright Teravision Games

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AUR_AbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAUR_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void OnAbilityActorInfoSet();
protected:

	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
	
};

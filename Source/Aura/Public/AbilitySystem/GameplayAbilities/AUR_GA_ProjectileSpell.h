// Copyright Teravision Games

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GameplayAbilities/AUR_GameplayAbility.h"
#include "AUR_GA_ProjectileSpell.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAUR_GA_ProjectileSpell : public UAUR_GameplayAbility
{
	GENERATED_BODY()

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};

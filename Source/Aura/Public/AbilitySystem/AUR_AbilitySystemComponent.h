// Copyright Teravision Games

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AUR_AbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTagsSignature, const FGameplayTagContainer& /*AssetTags*/);

/**
 * 
 */
UCLASS()
class AURA_API UAUR_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

    bool bHasInfoBeenSet = false;
    
	void OnAbilityActorInfoSet();
	
	FEffectAssetTagsSignature EffectAssetTagsDelegate;

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);

	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	
protected:

	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
	
};

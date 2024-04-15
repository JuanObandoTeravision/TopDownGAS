// Copyright Teravision Games


#include "AbilitySystem/AUR_AbilitySystemComponent.h"
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AbilitySystemComponent::OnAbilityActorInfoSet()
{
    if(bHasInfoBeenSet)
    {
		return;
    }
    
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAUR_AbilitySystemComponent::EffectApplied);
	bHasInfoBeenSet = true;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	
	EffectAssetTagsDelegate.Broadcast(TagContainer);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

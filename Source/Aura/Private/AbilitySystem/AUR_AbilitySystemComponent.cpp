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
	//TODO THE DELEGATE IS CALLING TWICE, FOR SOME REASON.
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, "effwect");
	
	EffectAssetTagsDelegate.Broadcast(TagContainer);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

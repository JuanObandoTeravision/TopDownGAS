// Copyright Teravision Games


#include "AbilitySystem/AUR_AbilitySystemComponent.h"

#include "AUR_GameplayTags.h"
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AbilitySystemComponent::OnAbilityActorInfoSet()
{
    if(bHasInfoBeenSet)
    {
		return;
    }
    
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAUR_AbilitySystemComponent::EffectApplied);
	bHasInfoBeenSet = true;

	const FAUR_GameplayTags& GameplayTags = FAUR_GameplayTags::Get();
	GEngine->AddOnScreenDebugMessage(
		-1,
		10.f,
		FColor::Orange,
		FString::Printf(TEXT("Tag: %s"), *GameplayTags.Attributes_Secondary_Armor.ToString())
		);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	
	EffectAssetTagsDelegate.Broadcast(TagContainer);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

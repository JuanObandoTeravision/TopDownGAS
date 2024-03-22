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
	//TODO THE DELEGATE IS CALLING TWICE, FOR SOME REASON.
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	for (const FGameplayTag& Tag : TagContainer)
	{
		//TODO: Broadcast the tag to the Widget Controller
		const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, Msg);
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

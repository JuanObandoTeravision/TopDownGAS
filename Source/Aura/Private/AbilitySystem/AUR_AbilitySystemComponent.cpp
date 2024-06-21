
#include "AbilitySystem/AUR_AbilitySystemComponent.h"

#include "AUR_GameplayTags.h"
#include "AbilitySystem/GameplayAbilities/AUR_GameplayAbility.h"
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AbilitySystemComponent::OnAbilityActorInfoSet()
{
    if(bHasInfoBeenSet)
    {
		return;
    }
    
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAUR_AbilitySystemComponent::Client_EffectApplied);
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

void UAUR_AbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);

		if (const UAUR_GameplayAbility* AuraAbility = Cast<UAUR_GameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(AuraAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void UAUR_AbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void UAUR_AbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void UAUR_AbilitySystemComponent::Client_EffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	
	EffectAssetTagsDelegate.Broadcast(TagContainer);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Copyright Teravision Games


#include "UI/WidgetController/AUR_OverlayWidgetController.h"

#include "AUR_AttributeSet.h"
#include "AbilitySystem/AUR_AbilitySystemComponent.h"

void UAUR_OverlayWidgetController::BroadcastInitialValues()
{
	const UAUR_AttributeSet* AuraAttributeSet = CastChecked<UAUR_AttributeSet>(AttributeSet);

	OnHealthChangedDelegate.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChangedDelegate.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChangedDelegate.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChangedDelegate.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UAUR_OverlayWidgetController::BindCallbacksToDependencies()
{
	const UAUR_AttributeSet* AuraAttributeSet = CastChecked<UAUR_AttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UAUR_OverlayWidgetController::OnHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UAUR_OverlayWidgetController::OnMaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	AuraAttributeSet->GetManaAttribute()).AddUObject(this, &UAUR_OverlayWidgetController::OnManaChanged);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	AuraAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UAUR_OverlayWidgetController::OnMaxManaChanged);

	Cast<UAUR_AbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTagsDelegate.AddLambda(
				[this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				// For example, say that Tag = Message.HealthPotion
				// "Message.HealthPotion".MatchesTag("Message") will return True, "Message".MatchesTag("Message.HealthPotion") will return False
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag))
				{
					const FAUR_UIWidgetRow* Row = GetDataTableRowByTag<FAUR_UIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);
}
			}
		}
	);
}

void UAUR_OverlayWidgetController::OnHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChangedDelegate.Broadcast(Data.NewValue);
}

void UAUR_OverlayWidgetController::OnMaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChangedDelegate.Broadcast(Data.NewValue);
}

void UAUR_OverlayWidgetController::OnManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChangedDelegate.Broadcast(Data.NewValue);
}

void UAUR_OverlayWidgetController::OnMaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChangedDelegate.Broadcast(Data.NewValue);
}

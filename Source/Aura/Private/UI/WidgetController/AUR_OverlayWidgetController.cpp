// Copyright Teravision Games


#include "UI/WidgetController/AUR_OverlayWidgetController.h"

#include "AUR_AttributeSet.h"

void UAUR_OverlayWidgetController::BroadcastInitialValues()
{
	const UAUR_AttributeSet* AuraAttributeSet = CastChecked<UAUR_AttributeSet>(AttributeSet);

	OnHealthChangedDelegate.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChangedDelegate.Broadcast(AuraAttributeSet->GetMaxHealth());
}

void UAUR_OverlayWidgetController::BindCallbacksToDependencies()
{
	const UAUR_AttributeSet* AuraAttributeSet = CastChecked<UAUR_AttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UAUR_OverlayWidgetController::OnHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UAUR_OverlayWidgetController::OnMaxHealthChanged);
}

void UAUR_OverlayWidgetController::OnHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChangedDelegate.Broadcast(Data.NewValue);
}

void UAUR_OverlayWidgetController::OnMaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChangedDelegate.Broadcast(Data.NewValue);
}

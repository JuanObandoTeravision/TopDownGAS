// Copyright Teravision Games


#include "UI/WidgetController/AUR_OverlayWidgetController.h"

#include "AUR_AttributeSet.h"

void UAUR_OverlayWidgetController::BroadcastInitialValues()
{
	const UAUR_AttributeSet* AuraAttributeSet = CastChecked<UAUR_AttributeSet>(AttributeSet);

	OnHealthChangedDelegate.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChangedDelegate.Broadcast(AuraAttributeSet->GetMaxHealth());
}

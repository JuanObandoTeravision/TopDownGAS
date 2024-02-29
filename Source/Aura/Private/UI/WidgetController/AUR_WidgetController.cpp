// Copyright Teravision Games


#include "UI/WidgetController/AUR_WidgetController.h"

void UAUR_WidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams)
{
	PlayerController = WidgetControllerParams.PlayerController;
	PlayerState = WidgetControllerParams.PlayerState;
	AbilitySystemComponent = WidgetControllerParams.AbilitySystemComponent;
	AttributeSet = WidgetControllerParams.AttributeSet;
}

void UAUR_WidgetController::BroadcastInitialValues()
{
	
}

void UAUR_WidgetController::BindCallbacksToDependencies()
{
}

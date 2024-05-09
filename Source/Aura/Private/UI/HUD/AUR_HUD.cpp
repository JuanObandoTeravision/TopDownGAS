// Copyright Teravision Games


#include "UI/HUD/AUR_HUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/WidgetController/AUR_AttributeMenuWC.h"
#include "UI/WidgetController/AUR_OverlayWidgetController.h"
#include "UI/Widgets/AUR_UserWidget.h"

UAUR_OverlayWidgetController* AAUR_HUD::GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UAUR_OverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	
	return OverlayWidgetController;
}

void AAUR_HUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_AuraHUD"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	if(!Widget)
	{
		return;
	}

	OverlayWidget = Cast<UAUR_UserWidget>(Widget);

	if(!OverlayWidget)
	{
		return;
	}
	
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);

	//Both tell the widget who's its controller and create the controller, if needed. 
	OverlayWidget->SetWidgetController(GetOverlayWidgetController(WidgetControllerParams));

	//We broadcast initial values after the overlay widget controller is set in the function above
	OverlayWidgetController->BroadcastInitialValues();
	
	Widget->AddToViewport();
}

UAUR_AttributeMenuWC* AAUR_HUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAUR_AttributeMenuWC>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}
	return AttributeMenuWidgetController;
}

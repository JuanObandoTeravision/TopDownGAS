// Copyright Teravision Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/WidgetController/AUR_WidgetController.h"
#include "AUR_HUD.generated.h"

/**
 * 
 */

class UAUR_OverlayWidgetController;
class UAUR_UserWidget;
UCLASS()
class AURA_API AAUR_HUD : public AHUD
{
	GENERATED_BODY()

public:
	
	UAUR_OverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	UPROPERTY()
	TObjectPtr<UAUR_UserWidget>  OverlayWidget;

private:

	//This is the actual widget class that works as the main HUD for the game
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAUR_UserWidget> OverlayWidgetClass;

	//The overlay controller that will manage all the information that the widget needs
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAUR_OverlayWidgetController> OverlayWidgetControllerClass;

	//Reference to the overlay controller
	UPROPERTY()
	TObjectPtr<UAUR_OverlayWidgetController> OverlayWidgetController;


	
};

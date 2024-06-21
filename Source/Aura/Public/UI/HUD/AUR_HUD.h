
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/WidgetController/AUR_WidgetController.h"
#include "AUR_HUD.generated.h"

/**
 * 
 */

class UAUR_AttributeMenuWC;
class UAUR_OverlayWidgetController;
class UAUR_UserWidget;
UCLASS()
class AURA_API AAUR_HUD : public AHUD
{
	GENERATED_BODY()

public:

	//Works like a singleton, meaning that if there is no overlay widget controller already set, it creates it firts
	UAUR_OverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	UAUR_AttributeMenuWC* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);

	UPROPERTY()
	TObjectPtr<UAUR_UserWidget>  OverlayWidget;

private:

	UPROPERTY()
	TObjectPtr<UAUR_AttributeMenuWC> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAUR_AttributeMenuWC> AttributeMenuWidgetControllerClass;

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

// Copyright Teravision Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AUR_HUD.generated.h"

/**
 * 
 */

class UAUR_UserWidget;
UCLASS()
class AURA_API AAUR_HUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<UAUR_UserWidget>  OverlayWidget;

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAUR_UserWidget> OverlayWidgetClass;
	
};

// Copyright Teravision Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AUR_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAUR_UserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnWidgetControllerSet();
	
};

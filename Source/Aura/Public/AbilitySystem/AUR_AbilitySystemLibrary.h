// Copyright Teravision Games

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AUR_AbilitySystemLibrary.generated.h"


class UAUR_OverlayWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API UAUR_AbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|WidgetController")
	static UAUR_OverlayWidgetController * GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|WidgetController")
	static UAUR_AttributeMenuWC* GetAttributeMenuWidgetController(const UObject* WorldContextObject);
	
};

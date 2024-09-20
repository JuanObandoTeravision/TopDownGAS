
#pragma once

#include "CoreMinimal.h"
#include "Data/AUR_CharacterClassInfo.h"
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

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, EAUR_CharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC);
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|CharacterClassDefaults")
	static void GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC);
	
};

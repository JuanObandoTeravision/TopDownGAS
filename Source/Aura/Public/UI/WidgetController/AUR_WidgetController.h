// Copyright Teravision Games

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AUR_WidgetController.generated.h"

/**
 * 
 */

class UAbilitySystemComponent;
class APlayerState;
class APlayerController;
class UAttributeSet;

UCLASS()
class AURA_API UAUR_WidgetController : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;
	
};

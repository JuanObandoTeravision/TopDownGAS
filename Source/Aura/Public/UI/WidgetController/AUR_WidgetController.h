
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

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
	
	
	FWidgetControllerParams()
	{
		
	}
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
	: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS)
	{
		
	}
};


UCLASS()
class AURA_API UAUR_WidgetController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams);
	
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();
	virtual void BindCallbacksToDependencies();

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

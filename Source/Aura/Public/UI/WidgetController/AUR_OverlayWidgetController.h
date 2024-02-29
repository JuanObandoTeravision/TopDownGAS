// Copyright Teravision Games

#pragma once

#include "CoreMinimal.h"
#include "AUR_AttributeSet.h"
#include "UI/WidgetController/AUR_WidgetController.h"
#include "AUR_OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealtChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealtChangedSignature, float, NewMaxHealth);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class AURA_API UAUR_OverlayWidgetController : public UAUR_WidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnHealtChangedSignature OnHealthChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxHealtChangedSignature OnMaxHealthChangedDelegate;

protected:
	
	void OnHealthChanged(const FOnAttributeChangeData& Data) const;


	void OnMaxHealthChanged(const FOnAttributeChangeData& Data) const;
};

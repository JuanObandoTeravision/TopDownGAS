// Copyright Teravision Games

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AUR_WidgetController.h"
#include "AUR_AttributeSet.h"
#include "AUR_GameplayTags.h"
#include "AbilitySystem/Data/AUR_AttributeInfo.h"
#include "AUR_AttributeMenuWC.generated.h"

class UAttributeInfo;
struct FAuraAttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAuraAttributeInfo&, Info);

class UAUR_AttributeInfo;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UAUR_AttributeMenuWC : public UAUR_WidgetController
{
	GENERATED_BODY()

public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAUR_AttributeInfo> AttributeInfo;
private:

	void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;
};

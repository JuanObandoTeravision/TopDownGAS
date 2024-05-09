// Copyright Teravision Games

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AUR_WidgetController.h"
#include "AUR_AttributeMenuWC.generated.h"

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
	
};

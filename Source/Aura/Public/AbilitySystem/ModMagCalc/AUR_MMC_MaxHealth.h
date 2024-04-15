// Copyright Teravision Games

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "AUR_MMC_MaxHealth.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAUR_MMC_MaxHealth : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UAUR_MMC_MaxHealth();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:

	FGameplayEffectAttributeCaptureDefinition IntDef;
	
};

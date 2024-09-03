
#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AUR_GameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAUR_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	FScalableFloat Damage;
	
};

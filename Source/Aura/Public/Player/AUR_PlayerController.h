// Copyright Teravision Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AUR_PlayerController.generated.h"


class UInputMappingContext;

/**
 * 
 */
UCLASS()
class AURA_API AAUR_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAUR_PlayerController();
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;
	
};

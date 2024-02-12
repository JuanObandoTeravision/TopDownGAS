// Copyright Teravision Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AUR_PlayerController.generated.h"


class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

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
	
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);
	
};

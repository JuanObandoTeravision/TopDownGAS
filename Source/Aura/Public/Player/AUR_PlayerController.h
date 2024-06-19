// Copyright Teravision Games

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "AUR_PlayerController.generated.h"


class UAUR_AbilitySystemComponent;
class UAUR_InputConfig;
class IAUR_EnemyInterface;
class UInputMappingContext;
class UInputAction;
class USplineComponent;
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

	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);

	
	void CursorTrace();
	IAUR_EnemyInterface* LastHoveredActor;
	IAUR_EnemyInterface* CurrentHoveredActor;
	FHitResult CursorHit;

	
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	
	void AutoRun();
	
	UPROPERTY()
	TObjectPtr<UAUR_AbilitySystemComponent> AuraAbilitySystemComponent;

	UAUR_AbilitySystemComponent* GetASC();


	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UAUR_InputConfig> InputConfig;

	//Move with mouse cursor behavior

	//Where we click on the mouse to go. If we click on a place without navmesh, this becomes the last generated path point to go to said location
	FVector CachedDestination;
	float FollowTime;
	float ShortPressThreshold;
	bool bAutoRunning;
	bool bTargeting;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;
	
};

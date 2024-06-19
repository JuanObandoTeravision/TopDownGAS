// Copyright Teravision Games


#include "Player/AUR_PlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AUR_GameplayTags.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AUR_AbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/AUR_InputComponent.h"
#include "Interaction/AUR_EnemyInterface.h"
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

AAUR_PlayerController::AAUR_PlayerController()
{
	bReplicates = true;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
	ShortPressThreshold = 0.5f;
	bAutoRunning = false;
	bTargeting = false;
	AutoRunAcceptanceRadius = 50.f;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AAUR_PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
	AutoRun();
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void AAUR_PlayerController::AutoRun()
{
	if (!bAutoRunning)
	{
		return;	
	}

	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void AAUR_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if(Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void AAUR_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UAUR_InputComponent* AuraInputComponent = CastChecked<UAUR_InputComponent>(InputComponent);
	AuraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAUR_PlayerController::Move);
	AuraInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void AAUR_PlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void AAUR_PlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastHoveredActor = CurrentHoveredActor;
	CurrentHoveredActor = Cast<IAUR_EnemyInterface>(CursorHit.GetActor());

	/**
	 * Line trace from cursor. There are several scenarios:
	 *  A. LastHoveredActor is null && CurrentHoveredActor is null
	 *		- Do nothing
	 *	B. LastHoveredActor is null && CurrentHoveredActor is valid
	 *		- Highlight CurrentHoveredActor
	 *	C. LastHoveredActor is valid && CurrentHoveredActor is null
	 *		- UnHighlight LastHoveredActor
	 *	D. Both actors are valid, but LastHoveredActor != CurrentHoveredActor
	 *		- UnHighlight LastHoveredActor, and Highlight CurrentHoveredActor
	 *	E. Both actors are valid, and are the same actor
	 *		- Do nothing
	 */

	if (LastHoveredActor == nullptr)
	{
		if (CurrentHoveredActor != nullptr)
		{
			// Case B
			CurrentHoveredActor->HighlightActor();
		}
		else
		{
			// Case A - both are null, do nothing
		}
	}
	else // LastHoveredActor is valid
		{
		if (CurrentHoveredActor == nullptr)
		{
			// Case C
			LastHoveredActor->UnHighlightActor();
		}
		else // both actors are valid
			{
			if (LastHoveredActor != CurrentHoveredActor)
			{
				// Case D
				LastHoveredActor->UnHighlightActor();
				CurrentHoveredActor->HighlightActor();
			}
			else
			{
				// Case E - do nothing
			}
			}
		}
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void AAUR_PlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(3, 3.f, FColor::Red, FString::Printf(TEXT("Pressed, %s"), *InputTag.ToString()));

	if (InputTag.MatchesTagExact(FAUR_GameplayTags::Get().InputTag_LMB))
	{
		bTargeting = CurrentHoveredActor ? true : false;
		bAutoRunning = false;
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void AAUR_PlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(3, 3.f, FColor::Blue, FString::Printf(TEXT("Released, %s"), *InputTag.ToString()));
	if (GetASC() == nullptr) return;

	if (!InputTag.MatchesTagExact(FAUR_GameplayTags::Get().InputTag_LMB) || InputTag.MatchesTagExact(FAUR_GameplayTags::Get().InputTag_LMB) && bTargeting)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
		return;
	}
	
	const APawn* ControlledPawn = GetPawn();
	if (FollowTime <= ShortPressThreshold && ControlledPawn)
	{
		if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
		{
			Spline->ClearSplinePoints();
			for (const FVector& PointLoc : NavPath->PathPoints)
			{
				Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
				//DrawDebugSphere(GetWorld(), PointLoc, 8.f, 8, FColor::Green, false, 5.f);
			}
			bAutoRunning = true;
		}
	}
	FollowTime = 0.f;
	bTargeting = false;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void AAUR_PlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(3, 3.f, FColor::Green, FString::Printf(TEXT("Held, %s"), *InputTag.ToString()));
	if (GetASC() == nullptr) return;
	
	if (!InputTag.MatchesTagExact(FAUR_GameplayTags::Get().InputTag_LMB) || InputTag.MatchesTagExact(FAUR_GameplayTags::Get().InputTag_LMB) && bTargeting)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
		return;
	}

	if(InputTag.MatchesTagExact(FAUR_GameplayTags::Get().InputTag_LMB))
	{
		FollowTime += GetWorld()->GetDeltaSeconds();

		if (CursorHit.bBlockingHit)
		{
			CachedDestination = CursorHit.ImpactPoint;
		}

		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
UAUR_AbilitySystemComponent* AAUR_PlayerController::GetASC()
{
	if (AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent = Cast<UAUR_AbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AuraAbilitySystemComponent;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

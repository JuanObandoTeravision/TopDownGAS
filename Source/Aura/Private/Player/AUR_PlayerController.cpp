// Copyright Teravision Games


#include "Player/AUR_PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/AUR_EnemyInterface.h"
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

AAUR_PlayerController::AAUR_PlayerController()
{
	bReplicates = true;
}

void AAUR_PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void AAUR_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext, 0);

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

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAUR_PlayerController::Move);
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
	FHitResult CursorHit;
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

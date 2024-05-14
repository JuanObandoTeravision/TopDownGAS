// Copyright Teravision Games


#include "Characters/AUR_Character.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AUR_AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Player/AUR_PlayerController.h"
#include "Player/AUR_PlayerState.h"
#include "UI/HUD/AUR_HUD.h"

AAUR_Character::AAUR_Character()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void AAUR_Character::BeginPlay()
{
	Super::BeginPlay();
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void AAUR_Character::InitAbilityActorInfo()
{
	if(AAUR_PlayerState* PlayerStateRef = Cast<AAUR_PlayerState>(GetPlayerState()))
	{
		PlayerStateRef->GetAbilitySystemComponent()->InitAbilityActorInfo(PlayerStateRef, this);
		Cast<UAUR_AbilitySystemComponent>(PlayerStateRef->GetAbilitySystemComponent())->OnAbilityActorInfoSet();
		AbilitySystemComponent = PlayerStateRef->GetAbilitySystemComponent();
		AttributeSet = PlayerStateRef->GetAttributeSet();
	}
	
	//We check if player controller is valid, as clients only have their own player controller as valid.
	if(AAUR_PlayerController* PlayerController = Cast<AAUR_PlayerController>(GetController()))
	{
		if(AAUR_HUD* PlayerHUD = Cast<AAUR_HUD>(PlayerController->GetHUD()))
		{
			PlayerHUD->InitOverlay(PlayerController, GetPlayerState(), AbilitySystemComponent, AttributeSet);
		}
	}

	//this could be only initialized in server, as attributes are already being replicated
	InitializeDefaultAttributes();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void AAUR_Character::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void AAUR_Character::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//OnRep is called only on client
	InitAbilityActorInfo();
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int32 AAUR_Character::GetPlayerLevel()
{
	const AAUR_PlayerState* AuraPlayerState = GetPlayerState<AAUR_PlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetPlayerLevel();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Copyright Teravision Games


#include "Characters/AUR_Character.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Player/AUR_PlayerState.h"

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
		AbilitySystemComponent = PlayerStateRef->GetAbilitySystemComponent();
		AttributeSet = PlayerStateRef->GetAttributeSet();
		AbilitySystemComponent->InitAbilityActorInfo(PlayerStateRef, this);
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void AAUR_Character::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//PossessedBy only occurs on server
	InitAbilityActorInfo();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void AAUR_Character::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//OnRep is called only on client
	InitAbilityActorInfo();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

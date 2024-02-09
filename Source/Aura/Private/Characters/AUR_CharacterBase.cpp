// Copyright Teravision Games


#include "Characters/AUR_CharacterBase.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

AAUR_CharacterBase::AAUR_CharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void AAUR_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
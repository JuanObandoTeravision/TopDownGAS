// Copyright Teravision Games

#pragma once

#include "CoreMinimal.h"
#include "Characters/AUR_CharacterBase.h"
#include "AUR_Character.generated.h"

class AAUR_PlayerState;
/**
 * 
 */
UCLASS()
class AURA_API AAUR_Character : public AAUR_CharacterBase
{
	GENERATED_BODY()

public:
	AAUR_Character();

	virtual void BeginPlay() override;

#pragma region Ability System component

	virtual void InitAbilityActorInfo() override;

#pragma endregion Ability System component

#pragma region Possession

	virtual void PossessedBy(AController* NewController) override;

#pragma endregion Possesion

#pragma region Core
	
	virtual void OnRep_PlayerState() override;

#pragma endregion Core

#pragma region Combat Interface
	
	virtual int32 GetPlayerLevel() override;

#pragma endregion Combat Interface
};

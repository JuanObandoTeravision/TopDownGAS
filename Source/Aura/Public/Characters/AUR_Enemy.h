// Copyright Teravision Games

#pragma once

#include "CoreMinimal.h"
#include "Interaction/AUR_EnemyInterface.h"
#include "Characters/AUR_CharacterBase.h"
#include "AUR_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAUR_Enemy : public AAUR_CharacterBase, public IAUR_EnemyInterface
{
	GENERATED_BODY()

public:
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	
};

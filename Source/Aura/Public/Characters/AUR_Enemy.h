
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
				
	AAUR_Enemy();

#pragma region ACharacter

public:
	virtual void BeginPlay() override;

#pragma endregion ACharacter

#pragma region Enemy Interface

public:
	
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	UPROPERTY(BlueprintReadOnly)
	uint8 bIsHighlighted : 1;

#pragma endregion Enemy Interface

#pragma region CombatInterface
public:
	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/** end Combat Interface */
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
#pragma endregion CombatInterace

public:
	virtual void InitAbilityActorInfo() override;
	
};

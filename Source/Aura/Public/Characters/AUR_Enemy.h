
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/AUR_CharacterClassInfo.h"
#include "Interaction/AUR_EnemyInterface.h"
#include "Characters/AUR_CharacterBase.h"
#include "UI/WidgetController/AUR_OverlayWidgetController.h"
#include "AUR_Enemy.generated.h"


class UWidgetComponent;
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

#pragma region Components
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

#pragma endregion Components

#pragma region Ability System Interface

	virtual void InitializeDefaultAttributes() const override;

#pragma endregion Ability System Interface

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

#pragma region Attributes


	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;



#pragma endregion Attributes

public:
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	EAUR_CharacterClass CharacterClass = EAUR_CharacterClass::Warrior;
	
};

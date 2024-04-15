// Copyright Teravision Games

#pragma once

#include "CoreMinimal.h"
#include "../../../../../../../Games/Epic Games/UE_5.2/Engine/Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AbilitySystemInterface.h"
#include "Interaction/AUR_CombatInterface.h"
#include "GameFramework/Character.h"
#include "AUR_CharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;

class USkeletalMeshComponent;
UCLASS()
class AURA_API AAUR_CharacterBase : public ACharacter, public IAbilitySystemInterface, public IAUR_CombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAUR_CharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

#pragma region Ability System Interface
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	
	virtual void InitAbilityActorInfo();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> InitializeDefaultPrimaryAttributesEffect;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> InitializeDefaultSecondaryAttributesEffect;
	
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
	void InitializeDefaultAttributes() const;

#pragma endregion 
};

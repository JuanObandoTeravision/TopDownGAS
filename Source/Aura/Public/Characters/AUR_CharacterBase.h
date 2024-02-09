// Copyright Teravision Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AUR_CharacterBase.generated.h"

class USkeletalMeshComponent;
UCLASS()
class AURA_API AAUR_CharacterBase : public ACharacter
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
};

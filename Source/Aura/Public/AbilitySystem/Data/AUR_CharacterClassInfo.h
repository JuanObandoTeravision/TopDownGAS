

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AUR_CharacterClassInfo.generated.h"

class UGameplayEffect;
class UGameplayAbility;

UENUM(BlueprintType)
enum class EAUR_CharacterClass : uint8
{
	None,
	Elementalist,
	Warrior,
	Ranger
};

USTRUCT(BlueprintType)
struct FAUR_CharacterClassDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TSubclassOf<UGameplayEffect> PrimaryAttributesGameplayEffectInit;
};

/**
 * 
 */
UCLASS()
class AURA_API UAUR_CharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TMap<EAUR_CharacterClass, FAUR_CharacterClassDefaultInfo> CharacterClassInformation;

	UPROPERTY(EditDefaultsOnly, Category = "Common Class Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributesGameplayEffectInit;

	UPROPERTY(EditDefaultsOnly, Category = "Common Class Defaults")
	TSubclassOf<UGameplayEffect> VitalAttributesGameplayEffectInit;

	UPROPERTY(EditDefaultsOnly, Category = "Common Class Defaults")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;

	FAUR_CharacterClassDefaultInfo GetClassDefaultInfo(EAUR_CharacterClass CharacterClass);
};

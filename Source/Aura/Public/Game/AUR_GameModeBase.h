
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AUR_GameModeBase.generated.h"

/**
 * 
 */

class UAUR_CharacterClassInfo;
UCLASS()
class AURA_API AAUR_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UAUR_CharacterClassInfo> CharacterClassInfo;
	
};

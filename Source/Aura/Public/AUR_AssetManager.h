
#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AUR_AssetManager.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAUR_AssetManager : public UAssetManager
{
	GENERATED_BODY()
public:

	static UAUR_AssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};

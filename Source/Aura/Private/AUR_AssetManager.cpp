

#include "AUR_AssetManager.h"

#include "AUR_GameplayTags.h"

UAUR_AssetManager& UAUR_AssetManager::Get()
{
	check(GEngine);

	UAUR_AssetManager* AuraAssetManager = Cast<UAUR_AssetManager>(GEngine->AssetManager);
	return *AuraAssetManager;
}

void UAUR_AssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FAUR_GameplayTags::InitializeNativeGameplayTags();
}

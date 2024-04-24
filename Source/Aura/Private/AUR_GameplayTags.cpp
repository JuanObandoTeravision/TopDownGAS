// Copyright Teravision Games


#include "AUR_GameplayTags.h"

#include "GameplayTagsManager.h"

FAUR_GameplayTags FAUR_GameplayTags::GameplayTags;

void FAUR_GameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reduces damage taken, improves Block Chance"));
}
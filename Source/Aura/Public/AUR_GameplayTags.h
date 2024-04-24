// Copyright Teravision Games

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"


struct FAUR_GameplayTags
{
 public:
	static const FAUR_GameplayTags& Get() { return GameplayTags;}
 static void InitializeNativeGameplayTags();

 FGameplayTag Attributes_Secondary_Armor;
  
 protected:

 private:
  static FAUR_GameplayTags GameplayTags;
};

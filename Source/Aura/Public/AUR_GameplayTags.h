// Copyright Teravision Games

#pragma once

#include "CoreMinimal.h"


struct FAUR_GameplayTags
{
public:
 static const FAUR_GameplayTags& Get() { return GameplayTags;}
 static void InitializeNativeGameplayTags();
protected:

private:
 static FAUR_GameplayTags GameplayTags;
};
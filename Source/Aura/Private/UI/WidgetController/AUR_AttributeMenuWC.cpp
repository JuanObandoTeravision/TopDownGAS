// Copyright Teravision Games


#include "UI/WidgetController/AUR_AttributeMenuWC.h"

#include "AUR_AttributeSet.h"
#include "AUR_GameplayTags.h"
#include "AbilitySystem/Data/AUR_AttributeInfo.h"

void UAUR_AttributeMenuWC::BindCallbacksToDependencies()
{
	
}

void UAUR_AttributeMenuWC::BroadcastInitialValues()
{
	UAUR_AttributeSet* AS = CastChecked<UAUR_AttributeSet>(AttributeSet);

	check(AttributeInfo);

	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(FAUR_GameplayTags::Get().Attributes_Primary_Strength);
	Info.AttributeValue = AS->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);
}

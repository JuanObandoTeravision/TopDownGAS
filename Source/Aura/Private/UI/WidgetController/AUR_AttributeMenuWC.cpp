// Copyright Teravision Games


#include "UI/WidgetController/AUR_AttributeMenuWC.h"

#include "AUR_AttributeSet.h"
#include "AUR_GameplayTags.h"
#include "AbilitySystem/Data/AUR_AttributeInfo.h"

void UAUR_AttributeMenuWC::BindCallbacksToDependencies()
{
	UAUR_AttributeSet* AS = CastChecked<UAUR_AttributeSet>(AttributeSet);
	check(AttributeInfo);
	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
		[this, Pair](const FOnAttributeChangeData& Data)
		{
			BroadcastAttributeInfo(Pair.Key, Pair.Value());
		}
	);
	}
}

void UAUR_AttributeMenuWC::BroadcastInitialValues()
{
	UAUR_AttributeSet* AS = CastChecked<UAUR_AttributeSet>(AttributeSet);

	check(AttributeInfo);
	
	for (auto& Pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
}

void UAUR_AttributeMenuWC::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}

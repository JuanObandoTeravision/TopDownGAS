// Copyright Teravision Games


#include "AbilitySystem/AUR_AbilitySystemLibrary.h"

#include "AUR_AttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "UI/WidgetController/AUR_WidgetController.h"

#include "Player/AUR_PlayerState.h"
#include "UI/HUD/AUR_HUD.h"

UAUR_OverlayWidgetController* UAUR_AbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AAUR_HUD* AuraHUD = Cast<AAUR_HUD>(PC->GetHUD()))
		{
			AAUR_PlayerState* PS = PC->GetPlayerState<AAUR_PlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAUR_AttributeMenuWC* UAUR_AbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AAUR_HUD* AuraHUD = Cast<AAUR_HUD>(PC->GetHUD()))
		{
			AAUR_PlayerState* PS = PC->GetPlayerState<AAUR_PlayerState>();;
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return AuraHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

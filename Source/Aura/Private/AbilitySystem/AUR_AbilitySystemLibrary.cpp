

#include "AbilitySystem/AUR_AbilitySystemLibrary.h"

#include "AUR_AttributeSet.h"
#include "AbilitySystem/Data/AUR_CharacterClassInfo.h"
#include "Game/AUR_GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/WidgetController/AUR_WidgetController.h"

#include "Player/AUR_PlayerState.h"
#include "UI/HUD/AUR_HUD.h"
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void UAUR_AbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject,
	EAUR_CharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	const AAUR_GameModeBase* AuraGameMode = Cast<AAUR_GameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (AuraGameMode == nullptr) return;

	const AActor* AvatarActor = ASC->GetAvatarActor();

	UAUR_CharacterClassInfo* CharacterClassInfo = AuraGameMode->CharacterClassInfo;
	const FAUR_CharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributesGameplayEffectInit, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributesGameplayEffectInit, Level, SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributesGameplayEffectInit, Level, VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}

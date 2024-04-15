// Copyright Teravision Games


#include "AUR_AttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

UAUR_AttributeSet::UAUR_AttributeSet()
{
	
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAUR_AttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAUR_AttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAUR_AttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAUR_AttributeSet, Vigor, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAUR_AttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAUR_AttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAUR_AttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAUR_AttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	
	// Secondary Attributes

	DOREPLIFETIME_CONDITION_NOTIFY(UAUR_AttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAUR_AttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAUR_AttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAUR_AttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAUR_AttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAUR_AttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAUR_AttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);	
	DOREPLIFETIME_CONDITION_NOTIFY(UAUR_AttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);	
	DOREPLIFETIME_CONDITION_NOTIFY(UAUR_AttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);	
	DOREPLIFETIME_CONDITION_NOTIFY(UAUR_AttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FAUR_EffectProperties EffectProperties;
	SetEffectProperties(Data, EffectProperties);

	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAUR_AttributeSet, Health, OldHealth);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAUR_AttributeSet, MaxHealth, OldMaxHealth);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAUR_AttributeSet, Mana, OldMana);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAUR_AttributeSet, MaxMana, OldMaxMana);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAUR_AttributeSet, Strength, OldStrength);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAUR_AttributeSet, Intelligence, OldIntelligence);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAUR_AttributeSet, Resilience, OldResilience);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAUR_AttributeSet, Vigor, OldVigor);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAUR_AttributeSet, Armor, OldArmor);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAUR_AttributeSet, ArmorPenetration, OldArmorPenetration);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAUR_AttributeSet, BlockChance, OldBlockChance);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAUR_AttributeSet, CriticalHitChance, OldCriticalHitChance);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAUR_AttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAUR_AttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAUR_AttributeSet, HealthRegeneration, OldHealthRegeneration);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAUR_AttributeSet, ManaRegeneration, OldManaRegeneration);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UAUR_AttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FAUR_EffectProperties& EffectProperties) const
{
	// Source = causer of the effect, Target = target of the effect (owner of this AS)

	EffectProperties.EffectContextHandle = Data.EffectSpec.GetContext();
	EffectProperties.SourceASC = EffectProperties.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(EffectProperties.SourceASC) && EffectProperties.SourceASC->AbilityActorInfo.IsValid() && EffectProperties.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		EffectProperties.SourceAvatarActor = EffectProperties.SourceASC->AbilityActorInfo->AvatarActor.Get();
		EffectProperties.SourceController = EffectProperties.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (EffectProperties.SourceController == nullptr && EffectProperties.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(EffectProperties.SourceAvatarActor))
			{
				EffectProperties.SourceController = Pawn->GetController();
			}
		}
		if (EffectProperties.SourceController)
		{
			EffectProperties.SourceCharacter = Cast<ACharacter>(EffectProperties.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		EffectProperties.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		EffectProperties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		EffectProperties.TargetCharacter = Cast<ACharacter>(EffectProperties.TargetAvatarActor);
		EffectProperties.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(EffectProperties.TargetAvatarActor);
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

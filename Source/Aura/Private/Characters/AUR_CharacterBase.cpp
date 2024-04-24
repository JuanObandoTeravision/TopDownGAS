// Copyright Teravision Games


#include "Characters/AUR_CharacterBase.h"

#include "AbilitySystemComponent.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

AAUR_CharacterBase::AAUR_CharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

UAbilitySystemComponent* AAUR_CharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void AAUR_CharacterBase::InitAbilityActorInfo()
{
	
}//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void AAUR_CharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void AAUR_CharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf( InitializeDefaultPrimaryAttributesEffect, 1.f);
	ApplyEffectToSelf( InitializeDefaultSecondaryAttributesEffect, 1.f);
	ApplyEffectToSelf( InitializeVitalAttributesEffect, 1.f);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void AAUR_CharacterBase::BeginPlay()
{
	Super::BeginPlay();

	
	
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
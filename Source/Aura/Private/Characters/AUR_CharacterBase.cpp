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
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void AAUR_CharacterBase::InitializePrimaryAttributes() const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(InitializeDefaultPrimaryAttributesEffect);
	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(InitializeDefaultPrimaryAttributesEffect, 1.f, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void AAUR_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
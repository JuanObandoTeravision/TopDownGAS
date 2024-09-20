
#include "Characters/AUR_CharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AUR_AbilitySystemComponent.h"
#include "Aura/Aura.h"
#include "Components/CapsuleComponent.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

AAUR_CharacterBase::AAUR_CharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

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

void AAUR_CharacterBase::AddCharacterAbilities() const
{
	UAUR_AbilitySystemComponent* AuraASC = CastChecked<UAUR_AbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	AuraASC->AddCharacterAbilities(StartupAbilities);
}

UAnimMontage* AAUR_CharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void AAUR_CharacterBase::Die()
{
	
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	MulticastHandleDeath();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void AAUR_CharacterBase::Dissolve()
{
	if (IsValid(DissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
		GetMesh()->SetMaterial(0, DynamicMatInst);
		BP_StartDissolveTimeline(DynamicMatInst);
	}
	if (IsValid(WeaponDissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);
		Weapon->SetMaterial(0, DynamicMatInst);
		BP_StartWeaponDissolveTimeline(DynamicMatInst);
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void AAUR_CharacterBase::MulticastHandleDeath_Implementation()
{
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Dissolve();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void AAUR_CharacterBase::BeginPlay()
{
	Super::BeginPlay();

	
	
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

FVector AAUR_CharacterBase::GetCombatSocketLocation()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

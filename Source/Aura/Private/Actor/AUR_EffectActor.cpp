// Copyright Teravision Games


#include "Actor/AUR_EffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


// Sets default values
AAUR_EffectActor::AAUR_EffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
}

void AAUR_EffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAUR_EffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if (TargetASC == nullptr) return;

	check(GameplayEffectClass);
	
	/**
	 * Specs first need a context to work. The Context Handle is just a wrapper that contains an internal gameplay effect context, that is,
	 * important information regarding the effect, such as source, target, etc. Every ASC can make a context, then you can add the appropiate info 
	 */
	
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	/**
	 * Remember, a spec is just a optimized version of a gameplay effect. A spec handle  will contain a TSharedPtr to the spec itself. It needs the context
	 * to knowledge of important information of the spec. You can also specify the spec level.
	 */
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);

	/**
	 * We de-reference the tshareptr because the function receives a FGameplayEffectSpec by reference, not the handle. The handle contains a ptr to the spec
	 */
	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}


// Copyright Teravision Games


#include "Actor/AUR_EffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


// Sets default values
AAUR_EffectActor::AAUR_EffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	bShouldDestroyOnEffectRemoval = false;
	InstantEffectApplicationPolicy = EAUR_EffectApplicationPolicy::DoNotApply;
	DurationEffectApplicationPolicy = EAUR_EffectApplicationPolicy::DoNotApply;
	InfiniteEffectApplicationPolicy = EAUR_EffectApplicationPolicy::DoNotApply;
	InfiniteEffectRemovalPolicy = EAUR_EffectRemovalPolicy::RemoveOnEndOverlap;
}

void AAUR_EffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAUR_EffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr)
	{
		return;
	}
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
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	const bool bIsInfinite =  EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && InfiniteEffectRemovalPolicy == EAUR_EffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}
}

void AAUR_EffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EAUR_EffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EAUR_EffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EAUR_EffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

void AAUR_EffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EAUR_EffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EAUR_EffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	
	if (InfiniteEffectApplicationPolicy == EAUR_EffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	
	if (InfiniteEffectRemovalPolicy == EAUR_EffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC))
		{
			return;
		}

		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
		{
			if (TargetASC == HandlePair.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}
		for (FActiveGameplayEffectHandle& Handle : HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}


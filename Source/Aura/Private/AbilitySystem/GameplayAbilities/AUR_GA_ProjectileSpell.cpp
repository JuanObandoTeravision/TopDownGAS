// Copyright Teravision Games


#include "AbilitySystem/GameplayAbilities/AUR_GA_ProjectileSpell.h"

#include "Actor/AUR_Projectile.h"
#include "Interaction/AUR_CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void UAUR_GA_ProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                              const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                              const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const bool bIsServer = HasAuthority(&ActivationInfo);
	if (!bIsServer)
	{
		return;
	}
	
	IAUR_CombatInterface* CombatInterface = Cast<IAUR_CombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		//TODO: Set the Projectile Rotation

		AAUR_Projectile* Projectile = GetWorld()->SpawnActorDeferred<AAUR_Projectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		//TODO: Give the Projectile a Gameplay Effect Spec for causing Damage.

		if(Projectile)
		{
			Projectile->FinishSpawning(SpawnTransform);
		}

	}
}


#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GameplayAbilities/AUR_GameplayAbility.h"
#include "AUR_GA_ProjectileSpell.generated.h"

class UGameplayEffect;
class AAUR_Projectile;
/**
 * 
 */
UCLASS()
class AURA_API UAUR_GA_ProjectileSpell : public UAUR_GameplayAbility
{
	GENERATED_BODY()

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable)
	virtual void SpawnProjectile(const FGameplayAbilityActivationInfo ActivationInfo, const FVector& ProjectileTargetLocation);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AAUR_Projectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;
};

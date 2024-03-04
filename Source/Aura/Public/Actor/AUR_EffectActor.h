// Copyright Teravision Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AUR_EffectActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UGameplayEffect;
UCLASS()
class AURA_API AAUR_EffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAUR_EffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UPROPERTY(EditAnywhere, BlueprintReadOnly,  Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

};

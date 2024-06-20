// Copyright Teravision Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AUR_Projectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class AURA_API AAUR_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAUR_Projectile();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereCollider;

};

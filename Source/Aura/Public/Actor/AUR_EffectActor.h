// Copyright Teravision Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AUR_EffectActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;
UCLASS()
class AURA_API AAUR_EffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAUR_EffectActor();

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;

};

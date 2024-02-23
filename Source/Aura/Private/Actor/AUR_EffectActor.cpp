// Copyright Teravision Games


#include "Actor/AUR_EffectActor.h"

#include "AbilitySystemInterface.h"
#include "AUR_AttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AAUR_EffectActor::AAUR_EffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AAUR_EffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAUR_EffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAUR_EffectActor::EndOverlap);
}

void AAUR_EffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: Change this to apply a Gameplay Effect. For now, using const_cast as a hack!
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UAUR_AttributeSet* AuraAttributeSet = Cast<UAUR_AttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAUR_AttributeSet::StaticClass()));

		UAUR_AttributeSet* MutableAuraAttributeSet = const_cast<UAUR_AttributeSet*>(AuraAttributeSet);
		MutableAuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void AAUR_EffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}


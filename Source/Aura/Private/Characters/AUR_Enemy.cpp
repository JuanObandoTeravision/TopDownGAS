// Copyright Teravision Games


#include "Characters/AUR_Enemy.h"

#include "AUR_AttributeSet.h"
#include "AbilitySystem/AUR_AbilitySystemComponent.h"
#include "Aura/Aura.h"
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

AAUR_Enemy::AAUR_Enemy()
{
	bIsHighlighted = false;
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
	AbilitySystemComponent = CreateDefaultSubobject<UAUR_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSet = CreateDefaultSubobject<UAUR_AttributeSet>("AttributeSet");
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void AAUR_Enemy::HighlightActor()
{
	bIsHighlighted = true;
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void AAUR_Enemy::UnHighlightActor()
{
	bIsHighlighted = false;
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

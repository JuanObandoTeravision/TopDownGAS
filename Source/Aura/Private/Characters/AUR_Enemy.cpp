
#include "Characters/AUR_Enemy.h"

#include "AUR_AttributeSet.h"
#include "AUR_GameplayTags.h"
#include "AbilitySystem/AUR_AbilitySystemComponent.h"
#include "AbilitySystem/AUR_AbilitySystemLibrary.h"
#include "Aura/Aura.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/Widgets/AUR_UserWidget.h"
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

AAUR_Enemy::AAUR_Enemy()
{
	bIsHighlighted = false;
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
	AbilitySystemComponent = CreateDefaultSubobject<UAUR_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSet = CreateDefaultSubobject<UAUR_AttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBarWidgetComponent");
	HealthBar->SetupAttachment(GetRootComponent());
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void AAUR_Enemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	if (UAUR_UserWidget* AuraUserWidget = Cast<UAUR_UserWidget>(HealthBar->GetUserWidgetObject()))
	{
		AuraUserWidget->SetWidgetController(this);
	}

	if (const UAUR_AttributeSet* AuraAS = Cast<UAUR_AttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

		AbilitySystemComponent->RegisterGameplayTagEvent(FAUR_GameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
			this,
			&AAUR_Enemy::HitReactTagChanged
		);

		OnMaxHealthChanged.Broadcast(AuraAS->GetMaxHealth());
		OnHealthChanged.Broadcast(AuraAS->GetHealth());
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void AAUR_Enemy::InitializeDefaultAttributes() const
{
	UAUR_AbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
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

int32 AAUR_Enemy::GetPlayerLevel()
{
	return Level;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void AAUR_Enemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void AAUR_Enemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	if(UAUR_AbilitySystemComponent* AUR_ASC = Cast<UAUR_AbilitySystemComponent>(AbilitySystemComponent))
	{
		AUR_ASC->OnAbilityActorInfoSet();
	}
	
	InitializeDefaultAttributes();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

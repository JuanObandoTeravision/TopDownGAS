// Copyright Teravision Games


#include "UI/HUD/AUR_HUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widgets/AUR_UserWidget.h"

void AAUR_HUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}

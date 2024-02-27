// Copyright Teravision Games


#include "UI/Widgets/AUR_UserWidget.h"

void UAUR_UserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	BP_WidgetControllerSet();
}

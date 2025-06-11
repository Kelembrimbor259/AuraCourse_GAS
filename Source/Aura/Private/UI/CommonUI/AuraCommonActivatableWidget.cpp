// Copyright Kelly259


#include "UI/CommonUI/AuraCommonActivatableWidget.h"

void UAuraCommonActivatableWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
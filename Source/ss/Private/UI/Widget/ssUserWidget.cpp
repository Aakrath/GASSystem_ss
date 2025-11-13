// Copyright SS Mechanics


#include "UI/Widget/ssUserWidget.h"

void UssUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
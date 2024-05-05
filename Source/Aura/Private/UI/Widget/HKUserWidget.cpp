// Copyright HeheKrazy


#include "UI/Widget/HKUserWidget.h"

void UHKUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}

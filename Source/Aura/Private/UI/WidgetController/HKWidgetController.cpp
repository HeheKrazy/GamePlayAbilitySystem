// Copyright HeheKrazy


#include "UI/WidgetController/HKWidgetController.h"

void UHKWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UHKWidgetController::BroadcastInitialValues()
{
}

void UHKWidgetController::BindCallbacksToDependencies()
{
}

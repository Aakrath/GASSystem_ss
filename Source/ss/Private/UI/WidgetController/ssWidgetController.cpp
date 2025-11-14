// Copyright SS Mechanics


#include "UI/WidgetController/ssWidgetController.h"

void UssWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UssWidgetController::BroadcastInitialValues()
{

}

void UssWidgetController::BindCallbacksToDependencies()
{
	
}
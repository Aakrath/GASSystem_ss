// Copyright SS Mechanics


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/ssAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UssAttributeSet* AuraAttributeSet = CastChecked<UssAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
}
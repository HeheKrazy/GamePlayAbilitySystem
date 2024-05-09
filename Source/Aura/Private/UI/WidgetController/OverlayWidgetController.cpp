// Copyright HeheKrazy


#include "UI/WidgetController/OverlayWidgetController.h"
#include "Characters/PlayerCharacter.h"
#include "AbilitySystem/HKAttributeSet.h"

void UOverlayWidgetController::BroadcastInitalValues()
{
	const UHKAttributeSet* HKAttributeSet = CastChecked<UHKAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(HKAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(HKAttributeSet->GetMaxHealth());
}

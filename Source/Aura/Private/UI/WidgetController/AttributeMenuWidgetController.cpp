// Copyright HeheKrazy


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/HKAttributeSet.h"
#include "HKGameplayTags.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UHKAttributeSet* AS = CastChecked<UHKAttributeSet>(AttributeSet);

	check(AttributeInfo);

	FHKAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(FHKGameplayTags::Get().Attributes_Primary_Strength);
	Info.AttributeValue = AS->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);
}

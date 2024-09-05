// Copyright HeheKrazy


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/HKAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include <Player/MyPlayerState.h>
#include "AbilitySystem/HKAbilitySystemComponent.h"


void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	check(AttributeInfo)

		for (auto& Pair : GetHKAS()->TagsToAttributes)
		{
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
				[this, Pair](const FOnAttributeChangeData& Data)
				{
					BroadcastAttributeInfo(Pair.Key, Pair.Value());
				}
			);
		}

		GetHKPS()->OnAttributePointChangedDelegate.AddLambda(
		[this](int32 Points)
		{
			AttributePointChangedDelegate.Broadcast(Points);
		}
	);
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	//UHKAttributeSet* AS = CastChecked<UHKAttributeSet>(AttributeSet);

	check(AttributeInfo);

	for (auto& Pair : GetHKAS()->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}

	//AMyPlayerState* HKPlayerState = CastChecked<AMyPlayerState>(PlayerState);
	AttributePointChangedDelegate.Broadcast(GetHKPS()->GetAttributePoints());

}

void UAttributeMenuWidgetController::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	//UHKAbilitySystemComponent* HKASC = CastChecked<UHKAbilitySystemComponent>(AbilitySystemComponent);
	GetHKASC()->UpgradeAttribute(AttributeTag);

}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	FHKAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}

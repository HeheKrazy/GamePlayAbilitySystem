// Copyright HeheKrazy


#include "UI/WidgetController/HKWidgetController.h"
#include "Player/MyPlayerState.h"
#include "Player/CharacterController.h"
#include "AbilitySystem/HKAbilitySystemComponent.h"
#include "AbilitySystem/HKAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"


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

void UHKWidgetController::BroadcastAbilityInfo()
{
	if (!GetHKASC()->bStartupAbilitiesGiven) return;

	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this](const FGameplayAbilitySpec& AbilitySpec)
		{
			FHKAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(HKAbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));
			Info.InputTag = HKAbilitySystemComponent->GetInputTagFromSpec(AbilitySpec);
			AbilityInfoDelegate.Broadcast(Info);
		});

	GetHKASC()->ForEachAbility(BroadcastDelegate);
}

ACharacterController* UHKWidgetController::GetHKPC()
{
	if (HKPlayerController == nullptr)
	{
		HKPlayerController = Cast<ACharacterController>(PlayerController);
	}
	return HKPlayerController;
}

AMyPlayerState* UHKWidgetController::GetHKPS()
{
	if (HKPlayerState == nullptr)
	{
		HKPlayerState = Cast<AMyPlayerState>(PlayerState);
	}
	return HKPlayerState;
}

UHKAbilitySystemComponent* UHKWidgetController::GetHKASC()
{
	if (HKAbilitySystemComponent == nullptr)
	{
		HKAbilitySystemComponent = Cast<UHKAbilitySystemComponent>(AbilitySystemComponent);
	}
	return HKAbilitySystemComponent;
}

UHKAttributeSet* UHKWidgetController::GetHKAS()
{
	if (HKAttributeSet == nullptr)
	{
		HKAttributeSet = Cast<UHKAttributeSet>(AttributeSet);
	}
	return HKAttributeSet;
}

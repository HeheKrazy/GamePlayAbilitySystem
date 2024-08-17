// Copyright HeheKrazy


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/HKAttributeSet.h"
#include "AbilitySystem/HKAbilitySystemComponent.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UHKAttributeSet* HKAttributeSet = CastChecked<UHKAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(HKAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(HKAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(HKAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(HKAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UHKAttributeSet* HKAttributeSet = CastChecked<UHKAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HKAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HKAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HKAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HKAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);

	if (UHKAbilitySystemComponent* HKASC = Cast<UHKAbilitySystemComponent>(AbilitySystemComponent))
	{
		if (HKASC->bStartupAbilitiesGiven)
		{
			OnInitializeStartupAbilities(HKASC);
		}
		else
		{
			HKASC->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::OnInitializeStartupAbilities);
		}


		HKASC->EffectAssetTags.AddLambda(
			[this](const FGameplayTagContainer& AssetTags)
			{
				for (const FGameplayTag& Tag : AssetTags)
				{
					FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));

					if (Tag.MatchesTag(MessageTag))
					{
						const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
						MessageWidgetRowDelegate.Broadcast(*Row);
					}
				}
			}
		);
	}
}

void UOverlayWidgetController::OnInitializeStartupAbilities(UHKAbilitySystemComponent* HKAbilitySystemComponent)
{
	//TODO get info about all given abilities, look up thier ability info and broadcast to widgets

	if (!HKAbilitySystemComponent->bStartupAbilitiesGiven) return;


}

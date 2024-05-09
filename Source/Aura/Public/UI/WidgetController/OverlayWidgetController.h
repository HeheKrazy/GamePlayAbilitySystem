// Copyright HeheKrazy

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/HKWidgetController.h"
#include "OverlayWidgetController.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UHKWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitalValues() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedSignature OnMaxHealthChanged;
};

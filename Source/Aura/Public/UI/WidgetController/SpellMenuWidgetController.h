// Copyright HeheKrazy

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/HKWidgetController.h"
#include "SpellMenuWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API USpellMenuWidgetController : public UHKWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
};

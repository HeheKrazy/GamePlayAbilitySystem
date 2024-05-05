// Copyright HeheKrazy

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HKUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UHKUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
private:
	
};

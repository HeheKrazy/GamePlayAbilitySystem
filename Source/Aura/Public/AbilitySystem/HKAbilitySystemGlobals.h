// Copyright HeheKrazy

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "HKAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UHKAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
	
};

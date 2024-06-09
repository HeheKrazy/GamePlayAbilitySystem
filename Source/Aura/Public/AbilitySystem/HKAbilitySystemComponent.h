// Copyright HeheKrazy

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "HKAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UHKAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void AbilityActorInfoSet();
protected:
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};

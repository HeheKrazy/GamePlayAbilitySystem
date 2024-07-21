// Copyright HeheKrazy


#include "AbilitySystem/HKAbilitySystemGlobals.h"
#include "HKAbilityTypes.h"

FGameplayEffectContext* UHKAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FHKGameplayEffectContext();
}

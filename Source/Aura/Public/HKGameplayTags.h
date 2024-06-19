// Copyright HeheKrazy

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * HKGameplayTags
 * 
 * Singleton containing native Gameplay Tags
 */

struct FHKGameplayTags
{
public:
	static const FHKGameplayTags& Get() { return GameplayTags; }

	static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Vigor;
	FGameplayTag Attributes_Primary_Resilience;

	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
protected:

private:
	static FHKGameplayTags GameplayTags;

};

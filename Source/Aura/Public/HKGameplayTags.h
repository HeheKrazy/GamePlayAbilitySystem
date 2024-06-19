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


protected:

private:
	static FHKGameplayTags GameplayTags;

};

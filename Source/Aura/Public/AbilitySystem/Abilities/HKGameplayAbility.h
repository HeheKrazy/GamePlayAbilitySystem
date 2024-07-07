// Copyright HeheKrazy

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "HKGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UHKGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartupInputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	FScalableFloat Damage;
};

// Copyright HeheKrazy

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/HKGameplayAbility.h"
#include "HKProjectileSpell.generated.h"


class AHKProjectile;
/**
 * 
 */
UCLASS()
class AURA_API UHKProjectileSpell : public UHKGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation);
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AHKProjectile> ProjectileClass;
};

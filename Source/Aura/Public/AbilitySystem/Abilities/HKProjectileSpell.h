// Copyright HeheKrazy

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/HKDamageGameplayAbility.h"
#include "HKProjectileSpell.generated.h"


class AHKProjectile;
class UGameplayEffect;
struct FGameplayTag;
/**
 * 
 */
UCLASS()
class AURA_API UHKProjectileSpell : public UHKDamageGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch = false, float PitchOverride = 0.f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AHKProjectile> ProjectileClass;

};

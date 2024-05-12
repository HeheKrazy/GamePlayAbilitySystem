// Copyright HeheKrazy

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HKEffectActor.generated.h"

class UGameplayEffect;
UCLASS()
class AURA_API AHKEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AHKEffectActor();
protected:
	virtual void BeginPlay() override;
	void ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UPROPERTY(EditAnywhere, Category = "AppliedEffects");
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

private:
};

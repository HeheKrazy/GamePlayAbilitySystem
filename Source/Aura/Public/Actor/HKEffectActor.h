// Copyright HeheKrazy

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HKEffectActor.generated.h"

class USphereComponent;
UCLASS()
class AURA_API AHKEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AHKEffectActor();
protected:
	virtual void BeginPlay() override;

private:
};

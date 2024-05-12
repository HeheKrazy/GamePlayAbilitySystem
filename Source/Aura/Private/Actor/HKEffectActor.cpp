// Copyright HeheKrazy


#include "Actor/HKEffectActor.h"


AHKEffectActor::AHKEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneComponent"));
}

void AHKEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

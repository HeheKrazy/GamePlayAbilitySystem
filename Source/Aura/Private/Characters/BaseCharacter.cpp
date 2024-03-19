// Copyright HeheKrazy


#include "Characters/BaseCharacter.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Copyright HeheKrazy

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	APlayerCharacter();

	/* Ability Sytem */
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	/* End Ability Sytem */

private:
	void InitAbilityActorInfo() override;
};

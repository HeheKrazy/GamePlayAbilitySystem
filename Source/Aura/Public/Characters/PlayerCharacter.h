// Copyright HeheKrazy

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Interaction/PlayerInterface.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API APlayerCharacter : public ABaseCharacter, public IPlayerInterface
{
	GENERATED_BODY()
public:
	APlayerCharacter();

	/* Ability Sytem */
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	/* End Ability Sytem */

	/* Start Combat Interface */

	virtual int32 GetPlayerLevel_Implementation() override;
	
	/* End Combat Interface */

	/* Start Player Interface */
	virtual void AddToXP_Implementation(int32 InXP) override;
	virtual void LevelUp_Implementation() override;
	/* End Player Interface */

private:
	void InitAbilityActorInfo() override;
};

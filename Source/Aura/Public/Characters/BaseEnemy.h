// Copyright HeheKrazy

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Interaction/OverlapInterface.h"
#include "BaseEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API ABaseEnemy : public ABaseCharacter, public IOverlapInterface
{
	GENERATED_BODY()
	
public:
	ABaseEnemy();

	/* OverlapInterface */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/* End OverlapInterface */

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
};

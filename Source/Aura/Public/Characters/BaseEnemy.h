// Copyright HeheKrazy

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Interaction/OverlapInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "BaseEnemy.generated.h"

class UWidgetComponent;
class UBehaviorTree;
class AHKAIController;
/**
 * 
 */
UCLASS()
class AURA_API ABaseEnemy : public ABaseCharacter, public IOverlapInterface
{
	GENERATED_BODY()
	
public:
	ABaseEnemy();
	virtual void PossessedBy(AController* NewController) override;

	/* OverlapInterface */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;
	/* End OverlapInterface */

	/* Start Combat Interface*/
	virtual int32 GetPlayerLevel() override;
	virtual void Die() override;
	/* End Combat Interface*/

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bHitReacting = false;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float BaseWalkSpeed = 250.f;	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 5.f;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	TObjectPtr<AActor> CombatTarget;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefualtAttributes() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AHKAIController> HKAIController;

	
private:
};

// Copyright HeheKrazy

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "HKAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UHKAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UHKAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/* Start Attributes */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes"	)
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	/* End Attributes */

	UFUNCTION()
	void OnRepHealth(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRepMaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRepMana(const FGameplayAttributeData& OldMana) const;

	UFUNCTION()
	void OnRepMaxMana(const FGameplayAttributeData& OldMaxMana) const;
};

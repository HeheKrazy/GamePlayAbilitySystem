// Copyright HeheKrazy


#include "AbilitySystem/ModModCalc/MMC_MaxMana.h"
#include "AbilitySystem/HKAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelDef.AttributeToCapture = UHKAttributeSet::GetVigorAttribute();
	IntelDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParamaeters;
	EvaluationParamaeters.SourceTags = SourceTags;
	EvaluationParamaeters.TargetTags = TargetTags;

	float Intel = 0.f;
	GetCapturedAttributeMagnitude(IntelDef, Spec, EvaluationParamaeters, Intel);
	Intel = FMath::Max<float>(Intel, 0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return 50.f + 2.5f * Intel + 10.f * PlayerLevel;
}
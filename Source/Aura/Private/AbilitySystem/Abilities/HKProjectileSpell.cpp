// Copyright HeheKrazy


#include "AbilitySystem/Abilities/HKProjectileSpell.h"
#include "Kismet/KismetSystemLibrary.h"

void UHKProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UKismetSystemLibrary::PrintString(this, FString("ActivateAbilityInfo (c++)"), true, true, FLinearColor::Yellow, 3);
}

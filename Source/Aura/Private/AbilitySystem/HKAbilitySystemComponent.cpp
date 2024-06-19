// Copyright HeheKrazy


#include "AbilitySystem/HKAbilitySystemComponent.h"
#include "HKGameplayTags.h"

void UHKAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UHKAbilitySystemComponent::EffectApplied);

	const FHKGameplayTags& GameplayTags = FHKGameplayTags::Get();
	//GameplayTags.Attributes_Secondary_Armor.ToString()
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Orange, FString::Printf(TEXT("Tag: %s"), *GameplayTags.Attributes_Secondary_Armor.ToString()));
}

void UHKAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	EffectAssetTags.Broadcast(TagContainer);

}

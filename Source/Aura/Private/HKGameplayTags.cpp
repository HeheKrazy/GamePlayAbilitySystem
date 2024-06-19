// Copyright HeheKrazy


#include "HKGameplayTags.h"
#include "GameplayTagsManager.h"

FHKGameplayTags FHKGameplayTags::GameplayTags;

void FHKGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reduces damage taken, improves block chance"));
}

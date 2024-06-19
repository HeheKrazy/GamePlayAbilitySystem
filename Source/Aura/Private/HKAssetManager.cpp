// Copyright HeheKrazy


#include "HKAssetManager.h"
#include "HKGameplayTags.h"

UHKAssetManager& UHKAssetManager::Get()
{
	check(GEngine);

	UHKAssetManager* HKAssetManager = Cast<UHKAssetManager>(GEngine->AssetManager);
	return *HKAssetManager;
}

void UHKAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	
	FHKGameplayTags::InitializeNativeGameplayTags();
}

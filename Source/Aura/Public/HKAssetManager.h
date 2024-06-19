// Copyright HeheKrazy

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "HKAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UHKAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	static UHKAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
	
};

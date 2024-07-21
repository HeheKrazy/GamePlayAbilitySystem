#pragma once

#include "GameplayEffectTypes.h"
#include "HKAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FHKGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:
	
	bool IsCriticalHit() const { return bIsCriticalHit; }
	bool IsBlockedHit() const { return bIsBlockedHit; }

	void SetIsCriticalHit(bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
	void SetIsBlockedHit(bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit;}

	// Returns the actual struct used for serialization, subclass must override this!
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}

	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FHKGameplayEffectContext* Duplicate() const
	{
		FHKGameplayEffectContext* NewContext = new FHKGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

		// Custom Serialization, Subclass must override this!
		virtual bool NetSerialize(FArchive & Ar, class UPackageMap* Map, bool& bOutSuccess);
	protected:

		UPROPERTY()
		bool bIsBlockedHit = false;

		UPROPERTY()
		bool bIsCriticalHit = false;
};

	template<>
	struct TStructOpsTypeTraits<FHKGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FHKGameplayEffectContext>
	{

		enum
		{
			WithNetSerializer = true,
			WithCopy = true
		};
	};
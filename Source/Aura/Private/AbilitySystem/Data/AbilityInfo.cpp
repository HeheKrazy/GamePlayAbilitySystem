// Copyright HeheKrazy


#include "AbilitySystem/Data/AbilityInfo.h"
#include "Aura/HKLogChannels.h"

FHKAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound) const
{
	for (const FHKAbilityInfo& Info : AbilityInformation)
	{
		if (Info.AbilityTag == AbilityTag)
		{
			return Info;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogHK, Error, TEXT("Can't find info for Ability Tag [%s] on AbilityInfo [%s]"), *AbilityTag.ToString(), *GetNameSafe(this));
	}

	return FHKAbilityInfo();
}
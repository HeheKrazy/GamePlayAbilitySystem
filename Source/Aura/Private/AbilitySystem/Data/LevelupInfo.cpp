// Copyright HeheKrazy


#include "AbilitySystem/Data/LevelupInfo.h"

int32 ULevelupInfo::FindLevelForXp(int32 XP)
{

	int32 Level = 1;
	bool bSearching = true;
	while (bSearching)
	{
		// LevelUpInformation[1] = level 1 info
		// LeveeUpInformation[2] = level 2 info
		if (LevelUpInformation.Num() - 1 <= Level) return Level;
	
		if (XP >= LevelUpInformation[Level].LevelUpRequirement)
		{
			++Level;
		}
		else
		{
			bSearching = false;
		}
	}
	return Level;
}

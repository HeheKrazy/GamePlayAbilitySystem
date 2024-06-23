// Copyright HeheKrazy


#include "AbilitySystem/Data/CharacterClassInfo.h"

FCharacterClassDefualtInfo UCharacterClassInfo::GetClassDefualtInfo(ECharacterClass CharacterClass)
{
	return CharacterClassInformation.FindChecked(CharacterClass);
}

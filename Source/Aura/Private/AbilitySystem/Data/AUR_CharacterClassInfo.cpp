


#include "AbilitySystem/Data/AUR_CharacterClassInfo.h"

FAUR_CharacterClassDefaultInfo UAUR_CharacterClassInfo::GetClassDefaultInfo(EAUR_CharacterClass CharacterClass)
{
	return CharacterClassInformation.FindChecked(CharacterClass);
}

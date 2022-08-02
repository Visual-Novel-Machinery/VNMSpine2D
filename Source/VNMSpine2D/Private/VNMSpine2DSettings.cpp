#include "VNMSpine2DSettings.h"

FVNMSpine2DCharacterDefinition UVNMSpine2DSettings::GetSpine2DCharacterById(const FName& CharacterId) const
{
	TArray<FVNMSpine2DCharacterDefinition*> CharacterDefinitions;
	Settings.Spine2DCharacterDefinitionsTable->GetAllRows("", CharacterDefinitions);
	for (auto* CharacterDefinition: CharacterDefinitions)
	{
		if (CharacterDefinition->CharacterId == CharacterId)
		{
			return *CharacterDefinition;
		}
	}

	return FVNMSpine2DCharacterDefinition();
}

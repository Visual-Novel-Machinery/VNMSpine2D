// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSpine2DCharacterDisplayWidget.h"

#include "VisualNovelMachinerySpine2D.h"

void UBaseSpine2DCharacterDisplayWidget::SetCharacterImageByCharacterIdAndEmotionId(const FName& InCharacterId, const FName& InEmotionId)
{
	if (CharacterId == InCharacterId && EmotionId == InEmotionId)
	{
		return;
	}
    
	CharacterId = InCharacterId;
	EmotionId = InEmotionId;

	CharacterDefinition = UVNMSettings::GetVNMSettings()->GetCharacterDefinitionById(CharacterId);

	if (!CharacterDefinition.IsValid())
	{
		UE_LOG(LogVNMSpine2D, Error, TEXT("UBaseSpine2DCharacterDisplayWidget::SetCharacterImageByCharacterIdAndEmotionId: Character Definition for Character Id not found!"));
		return;
	}
	FImageDefinition CharacterTexture;
	if (!CharacterDefinition.CharacterImagePerEmotion.Contains(EmotionId))
	{
		UE_LOG(LogVNMSpine2D, Error, TEXT("UBaseSpine2DCharacterDisplayWidget::SetCharacterImageByCharacterIdAndEmotionId: Texture for Emotion Id not found!"));
	}
	else
	{
		CharacterTexture = CharacterDefinition.CharacterImagePerEmotion[EmotionId];
	}
	
	Super::SetCharacterImageByCharacterIdAndEmotionId(InCharacterId, InEmotionId);
}

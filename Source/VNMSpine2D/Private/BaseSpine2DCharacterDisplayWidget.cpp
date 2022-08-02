// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSpine2DCharacterDisplayWidget.h"

#include "VisualNovelMachinerySpine2D.h"
#include "VNMSpine2DSettings.h"

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

	if (!CharacterDefinition.CharacterImagePerEmotion.Contains(EmotionId))
	{
		UE_LOG(LogVNMSpine2D, Error, TEXT("UBaseSpine2DCharacterDisplayWidget::SetCharacterImageByCharacterIdAndEmotionId: Character doesn't have an Emotion!"));
		return;
	}

	FVNMSpine2DCharacterDefinition SpineCharacterDefinition = UVNMSpine2DSettings::GetVNMSpine2DSettings()->GetSpine2DCharacterById(CharacterId);

	if (!SpineCharacterDefinition.IsValid())
	{
		SpineCharacterImage->SetVisibility(ESlateVisibility::Collapsed);
		CharacterImage->SetVisibility(ESlateVisibility::HitTestInvisible);
		Super::SetCharacterImageByCharacterIdAndEmotionId(InCharacterId, InEmotionId);
		return;
	}

	SpineCharacterImage->SetVisibility(ESlateVisibility::HitTestInvisible);
	CharacterImage->SetVisibility(ESlateVisibility::Collapsed);
	SpineCharacterImage->Atlas = SpineCharacterDefinition.Atlas;
	SpineCharacterImage->SkeletonData = SpineCharacterDefinition.SkeletonData;
	SpineCharacterImage->SetSkin(EmotionId.ToString());
	
	CharacterLayers.Empty();

	CharacterImage->InitializeImageLayers(0, FSlateBrush(), FLinearColor::Transparent);
}

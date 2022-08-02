// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSpine2DCharacterDisplayWidget.h"

#include "VNMSpine2D.h"
#include "VNMSpine2DSettings.h"

void UBaseSpine2DCharacterDisplayWidget::SetCharacterImageByCharacterIdAndEmotionId(const FName& InCharacterId, const FName& InEmotionId)
{
	if (CharacterId == InCharacterId && EmotionId == InEmotionId)
	{
		return;
	}

	CharacterDefinition = UVNMSettings::GetVNMSettings()->GetCharacterDefinitionById(InCharacterId);

	if (!CharacterDefinition.IsValid())
	{
		UE_LOG(LogVNMSpine2D, Error, TEXT("UBaseSpine2DCharacterDisplayWidget::SetCharacterImageByCharacterIdAndEmotionId: Character Definition for Character Id not found!"));
		return;
	}

	if (!CharacterDefinition.CharacterImagePerEmotion.Contains(InEmotionId))
	{
		UE_LOG(LogVNMSpine2D, Error, TEXT("UBaseSpine2DCharacterDisplayWidget::SetCharacterImageByCharacterIdAndEmotionId: Character doesn't have an Emotion!"));
		return;
	}

	FVNMSpine2DCharacterDefinition SpineCharacterDefinition = UVNMSpine2DSettings::GetVNMSpine2DSettings()->GetSpine2DCharacterById(InCharacterId);

	if (!SpineCharacterDefinition.IsValid())
	{
		SpineCharacterImage->SetVisibility(ESlateVisibility::Collapsed);
		CharacterImage->SetVisibility(ESlateVisibility::HitTestInvisible);
		Super::SetCharacterImageByCharacterIdAndEmotionId(InCharacterId, InEmotionId);
		return;
	}
    
	CharacterId = InCharacterId;
	EmotionId = InEmotionId;

	SpineCharacterImage->SetVisibility(ESlateVisibility::HitTestInvisible);
	CharacterImage->SetVisibility(ESlateVisibility::Collapsed);
	CharacterImage->SetRenderOpacity(0.f);
	SpineCharacterImage->Atlas = SpineCharacterDefinition.Atlas.LoadSynchronous();
	SpineCharacterImage->SkeletonData = SpineCharacterDefinition.SkeletonData.LoadSynchronous();
	SpineCharacterImage->SetAnimation(0, EmotionId.ToString().ToLower(), true);
	
	CharacterLayers.Empty();

	CharacterImage->InitializeImageLayers(0, FSlateBrush(), FLinearColor::Transparent);
}

void UBaseSpine2DCharacterDisplayWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	SpineCharacterImage->Tick(InDeltaTime, false);
}

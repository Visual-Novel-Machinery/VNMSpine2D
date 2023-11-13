// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSpine2DCharacterDisplayWidget.h"

#include "VNMSpine2D.h"
#include "VNMSpine2DSettings.h"

class FMoveSpine2DCharacterAction : public FPendingLatentAction
{
public:
	FMoveSpine2DCharacterAction(UBaseCharacterDisplayWidget* InCharacterDisplayWidget, float InStartPosition, float InTargetPosition)
		: CharacterDisplayWidget(InCharacterDisplayWidget)
		, StartPosition(InStartPosition)
		, TargetPosition(InTargetPosition)
	{
        
	}

	virtual void UpdateOperation(FLatentResponse& Response) override
	{
		Alpha = FMath::Min(1.0f, Alpha+Response.ElapsedTime());
		CharacterDisplayWidget->TickCharacterMove(Alpha, StartPosition, TargetPosition);
		Response.DoneIf(Alpha >= 1.f);

        
	}

protected:
	UBaseCharacterDisplayWidget* CharacterDisplayWidget;
	float StartPosition;
	float TargetPosition;
	float Alpha = 0.f;
	
};
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
	SpineCharacterImage->SetScaleX(SpineCharacterDefinition.Scale.X);
	SpineCharacterImage->SetScaleY(SpineCharacterDefinition.Scale.Y);
	
	CharacterLayers.Empty();

	CharacterImage->InitializeImageLayers(0, FSlateBrush(), FLinearColor::Transparent);
}

void UBaseSpine2DCharacterDisplayWidget::SetCharacterPosition(ECharacterPositioning InCharacterPositioning, const bool bMoveWithAnimation, int32 UUID)
{
	if (InCharacterPositioning == ECharacterPositioning::INHERIT)
	{
		return;
	}
    
	CharacterPositioning = InCharacterPositioning;

    
	auto CharacterPositioningValues = UVNMSettings::GetVNMSettings()->Settings.CharacterPositionValues;
	if (CharacterPositioningValues.Contains(InCharacterPositioning))
	{
		auto* CharacterImageCanvasSlot = Cast<UCanvasPanelSlot>(SpineCharacterImage->Slot);
        
		if (!CharacterImageCanvasSlot)
		{
			UE_LOG(LogVNMSpine2D, Error, TEXT("Character image is not inside of a canvas panel!"));
			return;
		}
        
		if (bMoveWithAnimation)
		{
			InitialAnchorPosition = CharacterImageCanvasSlot->GetAnchors().Minimum.X;
			FLatentActionManager& LatentActionManager = GetWorld()->GetLatentActionManager();
			if (!LatentActionManager.FindExistingAction<FMoveSpine2DCharacterAction>(this, UUID))
			{
				LatentActionManager.AddNewAction(this, UUID, new FMoveSpine2DCharacterAction(this, CharacterImageCanvasSlot->GetAnchors().Minimum.X, CharacterPositioningValues[InCharacterPositioning]));
			}
			return;
		}

		if (CharacterPositioning != ECharacterPositioning::TRUE_CENTER)
		{
			CharacterImageCanvasSlot->SetAnchors(FAnchors(CharacterPositioningValues[InCharacterPositioning], 1.f));
			CharacterImageCanvasSlot->SetAlignment(FVector2D(0.5f, 1.f));
			CharacterImageCanvasSlot->SetOffsets(FMargin(0.f));
		}
		else
		{
			CharacterImageCanvasSlot->SetAnchors(FAnchors(0.5f));
			CharacterImageCanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
			CharacterImageCanvasSlot->SetOffsets(FMargin(0.f));
		}
	}
}

void UBaseSpine2DCharacterDisplayWidget::TickCharacterMove(const float Alpha, const float StartPosition, const float TargetPosition)
{
	auto* CharacterImageCanvasSlot = Cast<UCanvasPanelSlot>(SpineCharacterImage->Slot);
	CharacterImageCanvasSlot->SetAnchors(FAnchors(FMath::Lerp(StartPosition, TargetPosition, Alpha), 1.f));
	CharacterImageCanvasSlot->SetAlignment(FVector2D(0.5f, 1.f));
	CharacterImageCanvasSlot->SetOffsets(FMargin(0.f));

	if (Alpha >= 1.f)
	{
		CharacterImageCanvasSlot->SetAnchors(FAnchors(TargetPosition, 1.f));
		OnTransitionComplete.Broadcast();
	}
}

void UBaseSpine2DCharacterDisplayWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	SpineCharacterImage->Tick(InDeltaTime, false);
}

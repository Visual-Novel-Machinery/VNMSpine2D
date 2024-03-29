// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacterDisplayWidget.h"
#include "../../../../SpinePlugin/Source/SpinePlugin/Public/SpineWidget.h"
#include "BaseSpine2DCharacterDisplayWidget.generated.h"

/**
 * 
 */
UCLASS()
class VNMSPINE2D_API UBaseSpine2DCharacterDisplayWidget : public UBaseCharacterDisplayWidget
{
	GENERATED_BODY()

public:
	virtual void SetCharacterImageByCharacterIdAndEmotionId(const FName& InCharacterId, const FName& InEmotionId) override;
	virtual void SetCharacterPosition(ECharacterPositioning InCharacterPositioning, const bool bMoveWithAnimation, int32 UUID) override;
	virtual void TickCharacterMove(const float Alpha, const float StartPosition, const float TargetPosition) override;

protected:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	USpineWidget* SpineCharacterImage;
};

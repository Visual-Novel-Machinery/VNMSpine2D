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
class VISUALNOVELMACHINERYSPINE2D_API UBaseSpine2DCharacterDisplayWidget : public UBaseCharacterDisplayWidget
{
	GENERATED_BODY()

public:
	virtual void SetCharacterImageByCharacterIdAndEmotionId(const FName& InCharacterId, const FName& InEmotionId) override;

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	USpineWidget* SpineCharacterImage;
};

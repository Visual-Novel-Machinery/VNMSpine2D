#pragma once

#include "CoreMinimal.h"
#include "SpineAtlasAsset.h"
#include "SpineSkeletonDataAsset.h"
#include "Engine/DataTable.h"

#include "VNMSpine2DSettings.generated.h"

USTRUCT(BlueprintType)
struct FVNMSpine2DCharacterDefinition : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	FName CharacterId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	TSoftObjectPtr<USpineAtlasAsset> Atlas;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	TSoftObjectPtr<USpineSkeletonDataAsset> SkeletonData;

	bool IsValid() const
	{
		return !CharacterId.IsNone();
	}
};

USTRUCT(BlueprintType)
struct FVisualNovelMachinerySpine2DSettings
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=DataTables)
	UDataTable* Spine2DCharacterDefinitionsTable;
};

/**
* Implements the settings for the Visual Novel Machinery Spine 2D plugin.
*/
UCLASS(config = Engine, defaultconfig)
class VNMSPINE2D_API UVNMSpine2DSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:	
	UFUNCTION(BlueprintPure, Category=Settings)
	static UVNMSpine2DSettings* GetVNMSpine2DSettings() { return GetMutableDefault<UVNMSpine2DSettings>(); }

	
	UFUNCTION(BlueprintPure, Category=Settings)
	FVNMSpine2DCharacterDefinition GetSpine2DCharacterById(const FName& CharacterId) const;

	/** Gets the settings container name for the settings, either Project or Editor */
	virtual FName GetContainerName() const override { return TEXT("Project"); }
	/** Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc. */
	virtual FName GetCategoryName() const override { return TEXT("Plugins"); }
	/** The unique name for your section of settings, uses the class's FName. */
	virtual FName GetSectionName() const override { return TEXT("VNMSpine2D"); }

#if WITH_EDITOR
	/** Gets the section text, uses the classes DisplayName by default. */
	virtual FText GetSectionText() const override { return NSLOCTEXT("VNMSpine2D", "RuntimeSettingsName", "Visual Novel Machinery Spine 2D"); }
	/** Gets the description for the section, uses the classes ToolTip by default. */
	virtual FText GetSectionDescription() const override { return NSLOCTEXT("VNMSpine2D", "RuntimeSettingsDescription", "Configure the Visual Novel Machinery Spine 2D plugin"); }

#endif

	/** List of all available CGs in the game */
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category=Settings)
	FVisualNovelMachinerySpine2DSettings Settings;
};

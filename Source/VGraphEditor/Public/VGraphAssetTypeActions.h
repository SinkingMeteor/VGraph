// Snake Game

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class VGRAPHEDITOR_API FVGraphAssetTypeActions : public FAssetTypeActions_Base
{
public:
	virtual FText GetName() const override { return INVTEXT("VGraph"); }
	virtual UClass* GetSupportedClass() const override;
	virtual FColor GetTypeColor() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;
	virtual uint32 GetCategories() override { return EAssetTypeCategories::Misc; }
};

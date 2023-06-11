// Snake Game


#include "VGraphAssetTypeActions.h"

#include "VGraph.h"


UClass* FVGraphAssetTypeActions::GetSupportedClass() const
{
	return UVGraph::StaticClass();
}

FColor FVGraphAssetTypeActions::GetTypeColor() const
{
	return FColor::Cyan;
}

void FVGraphAssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	FAssetTypeActions_Base::OpenAssetEditor(InObjects, EditWithinLevelEditor);
}

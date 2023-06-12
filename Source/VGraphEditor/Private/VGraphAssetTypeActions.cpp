// Snake Game


#include "VGraphAssetTypeActions.h"

#include "FVGraphAssetEditor.h"
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
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		UVGraph* Graph = Cast<UVGraph>(*ObjIt);
		if(Graph)
		{
			TSharedRef<FVGraphAssetEditor> GraphEditor = MakeShared<FVGraphAssetEditor>();
			GraphEditor->InitAssetEditor(Mode, EditWithinLevelEditor, Graph);
		}
	}
}

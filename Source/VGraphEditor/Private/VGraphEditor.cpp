// VGraph plugin copyright. All rights reserved.


#include "VGraphEditor.h"

#include "FVGraphPanelNodeFactory.h"

#define LOCTEXT_NAMESPACE "FVGraphRuntimeModule"

void FVGraphEditorModule::StartupModule()
{
	GraphAssetTypeActions = MakeShared<FVGraphAssetTypeActions>();
	FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(GraphAssetTypeActions.ToSharedRef());

	const TSharedPtr<FGraphPanelNodeFactory> GraphPanelNodeFactory = MakeShared<FVGraphPanelNodeFactory>();
	FEdGraphUtilities::RegisterVisualNodeFactory(GraphPanelNodeFactory);
}

void FVGraphEditorModule::ShutdownModule()
{
	if (!FModuleManager::Get().IsModuleLoaded("AssetTools")) return;
	FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(GraphAssetTypeActions.ToSharedRef());
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FVGraphEditorModule, VGraphEditor)
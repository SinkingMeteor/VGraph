// Copyright Epic Games, Inc. All Rights Reserved.

#include "VGraphEditor.h"

#define LOCTEXT_NAMESPACE "FVGraphRuntimeModule"

void FVGraphEditorModule::StartupModule()
{
	GraphAssetTypeActions = MakeShared<FVGraphAssetTypeActions>();
	FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(GraphAssetTypeActions.ToSharedRef());
}

void FVGraphEditorModule::ShutdownModule()
{
	if (!FModuleManager::Get().IsModuleLoaded("AssetTools")) return;
	FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(GraphAssetTypeActions.ToSharedRef());
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FVGraphEditorModule, VGraphEditor)
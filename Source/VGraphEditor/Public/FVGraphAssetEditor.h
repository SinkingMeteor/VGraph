// Snake Game

#pragma once

#include "CoreMinimal.h"
#include "VGraph.h"
#include "VGraphEditorSettings.h"

class IDetailsView;

class VGRAPHEDITOR_API FVGraphAssetEditor : public FAssetEditorToolkit, public FNotifyHook, public FGCObject
{
public:
	FVGraphAssetEditor();
	void InitAssetEditor(EToolkitMode::Type Mode, TSharedPtr<IToolkitHost> ToolkitHost, UVGraph* Graph);
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

protected:
	TSharedPtr<SGraphEditor> ViewportWidget;
	TSharedPtr<IDetailsView> PropertyWidget;
	TSharedPtr<IDetailsView> EditorSettingsWidget;
	
	UVGraphEditorSettings* EditorSettings;

	TSharedRef<SDockTab> SpawnTab_GraphCanvas(const FSpawnTabArgs& SpawnTabArgs);
	TSharedRef<SDockTab> SpawnTab_Properties(const FSpawnTabArgs& SpawnTabArgs);
	TSharedRef<SDockTab> SpawnTab_Settings(const FSpawnTabArgs& SpawnTabArgs);

	virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;
	void CreateEdGraph();
	void BindGraphCommands();
private:
	UVGraph* CurrentGraph;

	void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent);
	void CreateInternalWidgets();
	void OnSelectedNodesChanged(const TSet<UObject*>& Objects);
	void OnNodeDoubleClicked(UEdGraphNode* EdGraphNode);
	TSharedRef<SGraphEditor> CreateViewportWidget();
};

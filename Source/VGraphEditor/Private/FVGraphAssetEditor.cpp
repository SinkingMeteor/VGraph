// VGraph plugin copyright. All rights reserved.



#include "FVGraphAssetEditor.h"

#include "EdGraphUtilities.h"
#include "EditorStyleSet.h"
#include "EdVGraph.h"
#include "EdVGraphSchema.h"
#include "GraphEditorActions.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "LocalizationModule.h"
#include "VGraphEditorSettings.h"
#include "Framework/Commands/GenericCommands.h"
#include "Nodes/EdVNode.h"
#include "HAL/PlatformApplicationMisc.h"

#define LOCTEXT_NAMESPACE "AssetEditor_VGraph"

namespace
{
	const FName VGraphEditorAppName = FName(TEXT("VGraphEditorApp"));
	const FName VGraphPropertyID(TEXT("GenericGraphProperty"));
	const FName VGraphViewportID(TEXT("Viewport"));
	const FName VGraphEditorSettingsID(TEXT("GenericGraphEditorSettings"));
}

FVGraphAssetEditor::FVGraphAssetEditor() :
	EditorSettings(NewObject<UVGraphEditorSettings>()),
	CurrentGraph(nullptr)
{}

void FVGraphAssetEditor::CreateEdGraph(UVGraph* Graph)
{
	if(CurrentGraph->EditorGraph) return;
	
	CurrentGraph->EditorGraph = CastChecked<UEdVGraph>(FBlueprintEditorUtils::CreateNewGraph(Graph, NAME_None, UEdVGraph::StaticClass(), UEdVGraphSchema::StaticClass()));
	CurrentGraph->EditorGraph->bAllowDeletion = false;

	const UEdGraphSchema* Schema = CurrentGraph->EditorGraph->GetSchema();
	Schema->CreateDefaultNodesForGraph(*CurrentGraph->EditorGraph);
}

void FVGraphAssetEditor::InitAssetEditor(EToolkitMode::Type Mode, TSharedPtr<IToolkitHost> InToolkitHost, UVGraph* Graph)
{
	CurrentGraph = Graph;
	
	CreateEdGraph(Graph);
	
	FGenericCommands::Register();
	FGraphEditorCommands::Register();
	
	CreateInternalWidgets();

	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("VGraph_Layout_v1")
	->AddArea
	(
		FTabManager::NewPrimaryArea()
		->Split(FTabManager::NewSplitter()
			->SetOrientation(Orient_Horizontal)
			->SetSizeCoefficient(1.0f)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.2f)
				->SetHideTabWell(true)
				->AddTab(VGraphPropertyID, ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.6f)
				->SetHideTabWell(true)
				->AddTab(VGraphViewportID, ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.2f)
				->SetHideTabWell(true)
				->AddTab(VGraphEditorSettingsID, ETabState::OpenedTab)
			)
		)
	);
	
	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;
	FAssetEditorToolkit::InitAssetEditor(Mode, InToolkitHost, VGraphEditorAppName, StandaloneDefaultLayout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, CurrentGraph, false);
}

void FVGraphAssetEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_SoundCueEditor", "Sound Cue Editor"));
	const auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
	
	InTabManager->RegisterTabSpawner( VGraphViewportID, FOnSpawnTab::CreateSP(this, &FVGraphAssetEditor::SpawnTab_GraphCanvas) )
		.SetDisplayName( LOCTEXT("GraphCanvasTab", "Viewport") )
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "GraphEditor.EventGraph_16x"));

	InTabManager->RegisterTabSpawner( VGraphPropertyID, FOnSpawnTab::CreateSP(this, &FVGraphAssetEditor::SpawnTab_Properties) )
		.SetDisplayName( LOCTEXT("DetailsTab", "Details") )
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details"));

	InTabManager->RegisterTabSpawner( VGraphEditorSettingsID, FOnSpawnTab::CreateSP(this, &FVGraphAssetEditor::SpawnTab_Settings) )
		.SetDisplayName( LOCTEXT("PaletteTab", "Palette") )
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "Kismet.Tabs.Palette"));
}

void FVGraphAssetEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner( VGraphViewportID );
	InTabManager->UnregisterTabSpawner( VGraphPropertyID );
	InTabManager->UnregisterTabSpawner( VGraphEditorSettingsID );
}

FName FVGraphAssetEditor::GetToolkitFName() const
{
	return FName{"VGraph Editor Toolkit"};
}

FText FVGraphAssetEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "VGraph Editor");
}

FString FVGraphAssetEditor::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "VGraph ").ToString();
}

FLinearColor FVGraphAssetEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor::Green;
}

void FVGraphAssetEditor::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(CurrentGraph);
	Collector.AddReferencedObject(CurrentGraph->EditorGraph);
}

void FVGraphAssetEditor::SaveAsset_Execute()
{
	if(CurrentGraph && CurrentGraph->EditorGraph)
	{
		UEdVGraph* EdVGraph = Cast<UEdVGraph>(CurrentGraph->EditorGraph);
		EdVGraph->RebuildGraph(CurrentGraph);		
	}
	
	FAssetEditorToolkit::SaveAsset_Execute();
}

TSharedRef<SDockTab> FVGraphAssetEditor::SpawnTab_GraphCanvas(const FSpawnTabArgs& Args)
{
	check( Args.GetTabId() == VGraphViewportID );

	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab).Label(LOCTEXT("VGraphCanvasTitle", "Viewport"));

	if (ViewportWidget.IsValid())
	{
		SpawnedTab->SetContent(ViewportWidget.ToSharedRef());
	}

	return SpawnedTab;
}
TSharedRef<SDockTab> FVGraphAssetEditor::SpawnTab_Properties(const FSpawnTabArgs& Args)
{
	check( Args.GetTabId() == VGraphPropertyID );

	return SNew(SDockTab)
#if ENGINE_MAJOR_VERSION < 5
		.Icon(FEditorStyle::GetBrush("LevelEditor.Tabs.Details"))
#endif
		.Label(LOCTEXT("VGraphDetailsTitle", "Details"))
		[
			PropertyWidget.ToSharedRef()
		];
}
TSharedRef<SDockTab> FVGraphAssetEditor::SpawnTab_Settings(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == VGraphEditorSettingsID);

	return SNew(SDockTab)
#if ENGINE_MAJOR_VERSION < 5
		.Icon(FEditorStyle::GetBrush("LevelEditor.Tabs.Details"))
#endif 
		.Label(LOCTEXT("EditorSettings_Title", "VGraph Editor Setttings"))
		[
			EditorSettingsWidget.ToSharedRef()
		];
}

void FVGraphAssetEditor::CreateInternalWidgets()
{
	ViewportWidget = CreateViewportWidget();

	FDetailsViewArgs Args;
	Args.bHideSelectionTip = true;
	Args.NotifyHook = this;

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyWidget = PropertyModule.CreateDetailView(Args);
	PropertyWidget->SetObject(CurrentGraph);
	PropertyWidget->OnFinishedChangingProperties().AddSP(this, &FVGraphAssetEditor::OnFinishedChangingProperties);

	EditorSettingsWidget = PropertyModule.CreateDetailView(Args);
	EditorSettingsWidget->SetObject(EditorSettings);
}

void FVGraphAssetEditor::OnSelectedNodesChanged(const TSet<UObject*>& SelectedNodes)
{
	TArray<UObject*> Selections{};

	for (UObject* SelectionEntry : SelectedNodes)
	{
		const UEdVNode* EdNode = Cast<UEdVNode>(SelectionEntry);
		if(EdNode)
		{
			Selections.Add(EdNode->VGraphNode);
		}
	}

	if (Selections.Num() == 0) 
	{
		PropertyWidget->SetObject(CurrentGraph);
	}
	else
	{
		PropertyWidget->SetObjects(Selections);
	}
}

void FVGraphAssetEditor::OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent)
{
	if(!CurrentGraph) return;
	if(!CurrentGraph->EditorGraph) return;

	CurrentGraph->EditorGraph->GetSchema()->ForceVisualizationCacheClear();

	if(!ViewportWidget) return;

	FGraphPanelSelectionSet SelectedNodes = ViewportWidget->GetSelectedNodes();
	for (FGraphPanelSelectionSet::TConstIterator It{SelectedNodes}; It; ++It)
	{
		UEdVNode* EdNode = Cast<UEdVNode>(*It);
		if(!EdNode) continue;

		EdNode->VGraphNode->OnPropertiesChanged();
	}
}

void FVGraphAssetEditor::CreateCommandList()
{
	GraphEditorCommands = MakeShared<FUICommandList>();
	GraphEditorCommands->MapAction(FGenericCommands::Get().SelectAll,
		FExecuteAction::CreateSP(this, &FVGraphAssetEditor::SelectAllNodes),
		FCanExecuteAction::CreateSP(this, &FVGraphAssetEditor::CanSelectAllNodes));
	GraphEditorCommands->MapAction(FGenericCommands::Get().Delete,
	FExecuteAction::CreateSP(this, &FVGraphAssetEditor::DeleteSelectedNodes),
		FCanExecuteAction::CreateSP(this, &FVGraphAssetEditor::CanDeleteNodes));
	GraphEditorCommands->MapAction(FGenericCommands::Get().Copy,
	FExecuteAction::CreateSP(this, &FVGraphAssetEditor::CopySelectedNodes),
	FCanExecuteAction::CreateSP(this, &FVGraphAssetEditor::CanCopyNodes));
	GraphEditorCommands->MapAction(FGenericCommands::Get().Paste,
		FExecuteAction::CreateSP(this, &FVGraphAssetEditor::PasteNodes),
		FCanExecuteAction::CreateSP(this, &FVGraphAssetEditor::CanPasteNodes));
	GraphEditorCommands->MapAction(FGenericCommands::Get().Cut,
		FExecuteAction::CreateSP(this, &FVGraphAssetEditor::CutSelectedNodes),
		FCanExecuteAction::CreateSP(this, &FVGraphAssetEditor::CanCutNodes));
	GraphEditorCommands->MapAction(FGenericCommands::Get().Duplicate,
		FExecuteAction::CreateSP(this, &FVGraphAssetEditor::DuplicateNodes),
		FCanExecuteAction::CreateSP(this, &FVGraphAssetEditor::CanDuplicateNodes));
}

TSharedRef<SGraphEditor> FVGraphAssetEditor::CreateViewportWidget()
{
	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = LOCTEXT("AppearanceCornerText_VGraph", "VGraph");

	CreateCommandList();

	SGraphEditor::FGraphEditorEvents InEvents;
	InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this, &FVGraphAssetEditor::OnSelectedNodesChanged);

	return SNew(SGraphEditor)
		.AdditionalCommands(GraphEditorCommands)
		.IsEditable(true)
		.Appearance(AppearanceInfo)
		.GraphToEdit(CurrentGraph->EditorGraph)
		.GraphEvents(InEvents)
		.AutoExpandActionMenu(true)
		.ShowGraphStateOverlay(false);
}

void FVGraphAssetEditor::SelectAllNodes()
{
	if(!ViewportWidget.IsValid()) return;

	ViewportWidget->SelectAllNodes();
}

bool FVGraphAssetEditor::CanSelectAllNodes() const
{
	return true;
}

void FVGraphAssetEditor::DeleteSelectedNodes()
{
	if(!ViewportWidget.IsValid()) return;
	
	const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();

	if(SelectedNodes.Num() == 0) return;

	ViewportWidget->ClearSelectionSet();
	
	for (FGraphPanelSelectionSet::TConstIterator It{SelectedNodes}; It; ++It)
	{
		UEdGraphNode* EdGraphNode = Cast<UEdGraphNode>(*It);
		
		if(!It || !EdGraphNode->CanUserDeleteNode()) continue;

		EdGraphNode->Modify();
		const UEdGraphSchema* Schema = EdGraphNode->GetSchema();
		if(Schema)
		{
			Schema->BreakNodeLinks(*EdGraphNode);
		}
		EdGraphNode->DestroyNode();
	}

}

bool FVGraphAssetEditor::CanDeleteNodes() const
{
	const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();
	for (FGraphPanelSelectionSet::TConstIterator It{SelectedNodes}; It; ++It)
	{
		UEdVNode* EdVNode = Cast<UEdVNode>(*It);
		if(It && EdVNode->CanUserDeleteNode())
		{
			return true;
		}
	}
	
	return false;
}

void FVGraphAssetEditor::CopySelectedNodes()
{
	if(!ViewportWidget.IsValid()) return;
	
	FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();

	if(SelectedNodes.Num() == 0) return;

	for (FGraphPanelSelectionSet::TIterator It{SelectedNodes}; It; ++It)
	{
		UEdGraphNode* EdGraphNode = Cast<UEdGraphNode>(*It);
		
		if(!It || !EdGraphNode->CanDuplicateNode())
		{
			It.RemoveCurrent();
			continue;
		}
		
		EdGraphNode->PrepareForCopying();
	}
	
	FString ExportedText;
	FEdGraphUtilities::ExportNodesToText(SelectedNodes, /*out*/ ExportedText);
	FPlatformApplicationMisc::ClipboardCopy(*ExportedText);
}

bool FVGraphAssetEditor::CanCopyNodes() const
{
	const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();
	for (FGraphPanelSelectionSet::TConstIterator It{SelectedNodes}; It; ++It)
	{
		UEdVNode* EdVNode = Cast<UEdVNode>(*It);
		if(It && EdVNode->CanDuplicateNode())
		{
			return true;
		}
	}
	
	return false;
}

void FVGraphAssetEditor::PasteNodes()
{
	if(!ViewportWidget) return;

	UEdGraph* EdGraph = CurrentGraph->EditorGraph;

	const FScopedTransaction Transaction(FGenericCommands::Get().Paste->GetDescription());
	EdGraph->Modify();

	ViewportWidget->ClearSelectionSet();

	FString TextToImport;
	FPlatformApplicationMisc::ClipboardPaste(TextToImport);

	TSet<UEdGraphNode*> PastedNodes;
	FEdGraphUtilities::ImportNodesFromText(EdGraph, TextToImport, PastedNodes);

	FVector2D AvgNodePosition(0.0f, 0.0f);

	for (TSet<UEdGraphNode*>::TIterator It(PastedNodes); It; ++It)
	{
		UEdGraphNode* Node = *It;
		AvgNodePosition.X += Node->NodePosX;
		AvgNodePosition.Y += Node->NodePosY;
	}

	float InvNumNodes = 1.0f / float(PastedNodes.Num());
	AvgNodePosition.X *= InvNumNodes;
	AvgNodePosition.Y *= InvNumNodes;

	const FVector2D PasteLocation = ViewportWidget->GetPasteLocation();
	
	for (TSet<UEdGraphNode*>::TIterator It(PastedNodes); It; ++It)
	{
		UEdGraphNode* Node = *It;
		ViewportWidget->SetNodeSelection(Node, true);

		Node->NodePosX = (Node->NodePosX - AvgNodePosition.X) + PasteLocation.X;
		Node->NodePosY = (Node->NodePosY - AvgNodePosition.Y) + PasteLocation.Y;

		Node->SnapToGrid(16);
		Node->CreateNewGuid();
	}

	ViewportWidget->NotifyGraphChanged();

	if (CurrentGraph)
	{
		CurrentGraph->PostEditChange();
		CurrentGraph->MarkPackageDirty();
	}
}

bool FVGraphAssetEditor::CanPasteNodes() const
{
	if (!ViewportWidget.IsValid())
	{
		return false;
	}

	FString ClipboardContent;
	FPlatformApplicationMisc::ClipboardPaste(ClipboardContent);

	return FEdGraphUtilities::CanImportNodesFromText(ViewportWidget->GetCurrentGraph(), ClipboardContent);
}

void FVGraphAssetEditor::CutSelectedNodes()
{
	CopySelectedNodes();
	DeleteSelectedNodes();
}

bool FVGraphAssetEditor::CanCutNodes() const
{
	return CanCopyNodes() && CanDeleteNodes();
}

void FVGraphAssetEditor::DuplicateNodes()
{
	CopySelectedNodes();
	PasteNodes();
}

bool FVGraphAssetEditor::CanDuplicateNodes() const
{
	return CanCopyNodes();
}

FGraphPanelSelectionSet FVGraphAssetEditor::GetSelectedNodes() const
{
	FGraphPanelSelectionSet SelectedNodes{};

	if(ViewportWidget.IsValid())
	{
		SelectedNodes = ViewportWidget->GetSelectedNodes();
	}
	return SelectedNodes;
}

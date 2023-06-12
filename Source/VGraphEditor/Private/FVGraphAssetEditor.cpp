// Snake Game


#include "FVGraphAssetEditor.h"

#include "EditorStyleSet.h"
#include "EdVGraph.h"
#include "EdVGraphSchema.h"
#include "GraphEditorActions.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "LocalizationModule.h"

#define LOCTEXT_NAMESPACE "AssetEditor_VGraph"

namespace
{
	const FName VGraphEditorAppName = FName(TEXT("VGraphEditorApp"));
	
	const FName VGraphPropertyID(TEXT("GenericGraphProperty"));
	const FName VGraphViewportID(TEXT("Viewport"));
	const FName VGraphEditorSettingsID(TEXT("GenericGraphEditorSettings"));
}

FVGraphAssetEditor::FVGraphAssetEditor()
{
}

FVGraphAssetEditor::~FVGraphAssetEditor()
{
}

void FVGraphAssetEditor::CreateEdGraph()
{
	if (CurrentGraph->EditorGraph == nullptr)
	{
		CurrentGraph->EditorGraph = CastChecked<UEdVGraph>(FBlueprintEditorUtils::CreateNewGraph(CurrentGraph, NAME_None, UEdVGraph::StaticClass(), UEdVGraphSchema::StaticClass()));
		CurrentGraph->EditorGraph->bAllowDeletion = false;

		// Give the schema a chance to fill out any required nodes (like the results node)
		const UEdGraphSchema* Schema = CurrentGraph->EditorGraph->GetSchema();
		Schema->CreateDefaultNodesForGraph(*CurrentGraph->EditorGraph);
	}
}

void FVGraphAssetEditor::InitAssetEditor(EToolkitMode::Type Mode, TSharedPtr<IToolkitHost> InToolkitHost, UVGraph* Graph)
{
	CurrentGraph = Graph;

	CreateEdGraph();
	
	if(false)
	{
		Graph->SetFlags(EObjectFlags::RF_Transactional);
		//GEditor->RegisterForUndo(this);
	}

	FGraphEditorCommands::Register();
	
	//BindGraphCommands();
	CreateInternalWidgets();

	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_VGraphEditor_Layout_v1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.65f)
				->SetHideTabWell(true)
				->AddTab(VGraphViewportID, ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.225f)
				->SetHideTabWell(true)
				->AddTab(VGraphPropertyID, ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.125f)
				->SetHideTabWell(true)
				->AddTab(VGraphEditorSettingsID, ETabState::OpenedTab)
			)
		);

	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;
	FAssetEditorToolkit::InitAssetEditor(Mode, InToolkitHost, VGraphEditorAppName, StandaloneDefaultLayout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, CurrentGraph, false);
}

void FVGraphAssetEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_SoundCueEditor", "Sound Cue Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner( VGraphViewportID, FOnSpawnTab::CreateSP(this, &FVGraphAssetEditor::SpawnTab_GraphCanvas) )
		.SetDisplayName( LOCTEXT("GraphCanvasTab", "Viewport") )
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "GraphEditor.EventGraph_16x"));

	InTabManager->RegisterTabSpawner( VGraphPropertyID, FOnSpawnTab::CreateSP(this, &FVGraphAssetEditor::SpawnTab_Properties) )
		.SetDisplayName( LOCTEXT("DetailsTab", "Details") )
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));

	InTabManager->RegisterTabSpawner( VGraphEditorSettingsID, FOnSpawnTab::CreateSP(this, &FVGraphAssetEditor::SpawnTab_Settings) )
		.SetDisplayName( LOCTEXT("PaletteTab", "Palette") )
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "Kismet.Tabs.Palette"));
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
	//EditorSettingsWidget->SetObject(GenricGraphEditorSettings);
}

void FVGraphAssetEditor::OnSelectedNodesChanged(const TSet<UObject*>& Objects)
{
}

void FVGraphAssetEditor::OnNodeDoubleClicked(UEdGraphNode* EdGraphNode)
{
}

void FVGraphAssetEditor::OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent)
{
}

TSharedRef<SGraphEditor> FVGraphAssetEditor::CreateViewportWidget()
{
	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = LOCTEXT("AppearanceCornerText_VGraph", "VGraph");

	//CreateCommandList();

	SGraphEditor::FGraphEditorEvents InEvents;
	InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this, &FVGraphAssetEditor::OnSelectedNodesChanged);
	InEvents.OnNodeDoubleClicked = FSingleNodeEvent::CreateSP(this, &FVGraphAssetEditor::OnNodeDoubleClicked);

	return SNew(SGraphEditor)
		//.AdditionalCommands(GraphEditorCommands)
		.IsEditable(true)
		.Appearance(AppearanceInfo)
		.GraphToEdit(CurrentGraph->EditorGraph)
		.GraphEvents(InEvents)
		.AutoExpandActionMenu(true)
		.ShowGraphStateOverlay(false);
}

// Snake Game


#include "FVGraphAssetEditor.h"

#include "EditorStyleSet.h"
#include "EdVGraph.h"
#include "EdVGraphSchema.h"
#include "GraphEditorActions.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "LocalizationModule.h"
#include "VGraphEditorSettings.h"
#include "Framework/Commands/GenericCommands.h"

#define LOCTEXT_NAMESPACE "AssetEditor_VGraph"

namespace
{
	const FName VGraphEditorAppName = FName(TEXT("VGraphEditorApp"));
	
	const FName VGraphPropertyID(TEXT("GenericGraphProperty"));
	const FName VGraphViewportID(TEXT("Viewport"));
	const FName VGraphEditorSettingsID(TEXT("GenericGraphEditorSettings"));
}

FVGraphAssetEditor::FVGraphAssetEditor() :
	EditorGraph(nullptr),
	EditorSettings(NewObject<UVGraphEditorSettings>())
{}

void FVGraphAssetEditor::CreateEdGraph(UVGraph* Graph)
{
	EditorGraph = MakeShareable(CastChecked<UEdVGraph>(FBlueprintEditorUtils::CreateNewGraph(Graph, NAME_None, UEdVGraph::StaticClass(), UEdVGraphSchema::StaticClass())));
	EditorGraph->SetVGraph(Graph);
	EditorGraph->bAllowDeletion = false;

	const UEdGraphSchema* Schema = EditorGraph->GetSchema();
	Schema->CreateDefaultNodesForGraph(*EditorGraph);
}

void FVGraphAssetEditor::InitAssetEditor(EToolkitMode::Type Mode, TSharedPtr<IToolkitHost> InToolkitHost, UVGraph* Graph)
{
	CreateEdGraph(Graph);
	
	FGenericCommands::Register();
	FGraphEditorCommands::Register();
	
	BindGraphCommands();
	CreateInternalWidgets();

	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_VGraphEditor_Layout_v1")
			->AddArea
			(
				FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
				->Split
				(
					FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)->SetSizeCoefficient(0.9f)
					->Split
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(0.65f)
						->AddTab(VGraphViewportID, ETabState::OpenedTab)->SetHideTabWell(true)
					)
					->Split
					(
						FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
						->Split
						(
							FTabManager::NewStack()
							->SetSizeCoefficient(0.7f)
							->AddTab(VGraphPropertyID, ETabState::OpenedTab)->SetHideTabWell(true)
						)
						->Split
						(
							FTabManager::NewStack()
							->SetSizeCoefficient(0.3f)
							->AddTab(VGraphEditorSettingsID, ETabState::OpenedTab)
						)
					)
				)
			);
	
	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;
	FAssetEditorToolkit::InitAssetEditor(Mode, InToolkitHost, VGraphEditorAppName, StandaloneDefaultLayout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, EditorGraph->GetVGraph(), false);
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
	PropertyWidget->SetObject(EditorGraph->GetVGraph());
	PropertyWidget->OnFinishedChangingProperties().AddSP(this, &FVGraphAssetEditor::OnFinishedChangingProperties);

	EditorSettingsWidget = PropertyModule.CreateDetailView(Args);
	EditorSettingsWidget->SetObject(EditorSettings);
}

void FVGraphAssetEditor::OnSelectedNodesChanged(const TSet<UObject*>& Objects)
{
}

void FVGraphAssetEditor::OnNodeDoubleClicked(UEdGraphNode* EdGraphNode)
{
}

void FVGraphAssetEditor::OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent)
{
	if(!EditorGraph->GetVGraph()) return;

	EditorGraph->GetSchema()->ForceVisualizationCacheClear();
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
	InEvents.OnNodeDoubleClicked = FSingleNodeEvent::CreateSP(this, &FVGraphAssetEditor::OnNodeDoubleClicked);

	return SNew(SGraphEditor)
		.AdditionalCommands(GraphEditorCommands)
		.IsEditable(true)
		.Appearance(AppearanceInfo)
		.GraphToEdit(EditorGraph.Get())
		.GraphEvents(InEvents)
		.AutoExpandActionMenu(true)
		.ShowGraphStateOverlay(false);
}

void FVGraphAssetEditor::SelectAllNodes()
{
}

bool FVGraphAssetEditor::CanSelectAllNodes() const
{
	return true;
}

void FVGraphAssetEditor::DeleteSelectedNodes()
{
}

bool FVGraphAssetEditor::CanDeleteNodes() const
{
	return true;
}

void FVGraphAssetEditor::CopySelectedNodes()
{
}

bool FVGraphAssetEditor::CanCopyNodes() const
{
	return true;
}

void FVGraphAssetEditor::PasteNodes()
{
}

bool FVGraphAssetEditor::CanPasteNodes() const
{
	return true;
}

void FVGraphAssetEditor::CutSelectedNodes()
{
}

bool FVGraphAssetEditor::CanCutNodes() const
{
	return true;
}

void FVGraphAssetEditor::DuplicateNodes()
{
}

bool FVGraphAssetEditor::CanDuplicateNodes() const
{
	return true;
}

void FVGraphAssetEditor::BindGraphCommands()
{
}

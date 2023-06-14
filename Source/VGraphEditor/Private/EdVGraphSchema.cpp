// Snake Game


#include "EdVGraphSchema.h"

#include "EdVGraph.h"
#include "VGraph.h"
#include "Nodes/VStartNode.h"

#define LOCTEXT_NAMESPACE "AssetSchema_VGraph"

FVGraphSchemaAction_NewNode::FVGraphSchemaAction_NewNode(
	FText InNodeCategory,
	FText InMenuDesc,
	FText InToolTip,
	const int32 InGrouping,
	FText InKeywords,
	int32 InSectionID) :
	FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping, InKeywords, InSectionID)
{}

UEdGraphNode* FVGraphSchemaAction_NewNode::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
	const FScopedTransaction Transaction(LOCTEXT("VGraph_EditorNewNode", "VGraph Editor: New Node"));
	ParentGraph->Modify();
	if (FromPin != nullptr)
		FromPin->Modify();

	UEdVGraph* EdVGraph = Cast<UEdVGraph>(ParentGraph);
	UVGraph* VGraph = EdVGraph->GetVGraph();

	UVBaseNode* VNode = NewObject<UVBaseNode>(VGraph, NodeTemplate);
	VGraph->AddNode(VNode);
	
	UEdVNode* EdVNode = NewObject<UEdVNode>(ParentGraph);
	EdVNode->SetNode(VNode);
	EdVGraph->AddNode(EdVNode, true, bSelectNewNode);
	EdVGraph->NotifyGraphChanged();
	
	EdVNode->CreateNewGuid();
	EdVNode->PostPlacedNewNode();
	EdVNode->AllocateDefaultPins();
	EdVNode->AutowireNewNode(FromPin);

	EdVNode->NodePosX = Location.X;
	EdVNode->NodePosY = Location.Y;

	EdVGraph->SetFlags(RF_Transactional);
	EdVNode->SetFlags(RF_Transactional);

	return EdVNode;
}

void UEdVGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	Super::GetGraphContextActions(ContextMenuBuilder);

	TSharedPtr<FVGraphSchemaAction_NewNode> NewNodeSchemaAction = MakeShared<FVGraphSchemaAction_NewNode>(
		LOCTEXT("VGraphNodeAction_Category", "Create VGraph Node"),
		LOCTEXT("VGraphNodeAction_MenuDesc", "Create VGraph Node"),
		LOCTEXT("VGraphNodeAction_Tooltip", "Add here"), 0);
	NewNodeSchemaAction->SetTemplate(UVStartNode::StaticClass());
	ContextMenuBuilder.AddAction(NewNodeSchemaAction);
}

// VGraph plugin copyright. All rights reserved.



#include "EdVGraphSchema.h"
#include "EdVGraph.h"
#include "GraphEditorActions.h"
#include "VGraph.h"
#include "Framework/Commands/GenericCommands.h"
#include "Nodes/EdVNode.h"

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
	UVGraph* VGraph = CastChecked<UVGraph>(EdVGraph->GetOuter());

	UVBaseNode* VNode = NewObject<UVBaseNode>(VGraph, NodeTemplate);
	VGraph->AddNode(VNode);
	
	UEdVNode* EdVNode = NewObject<UEdVNode>(EdVGraph);
	EdVNode->VGraphNode = VNode;

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
	EdVNode->AutowireNewNode(FromPin);
	
	return EdVNode;
}

void UEdVGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	Super::GetGraphContextActions(ContextMenuBuilder);

	FText CreateCategory = LOCTEXT("VGraphNodeAction_Category", "Create");
	FText Tooltip = LOCTEXT("VGraphNodeAction_Tooltip", "Add here");
	
	for (TObjectIterator<UClass> It; It; ++It)
	{
		if (It->IsChildOf(UVBaseNode::StaticClass()) && !It->HasAnyClassFlags(CLASS_Abstract))
		{
			TSubclassOf<UVBaseNode> NodeType = *It;
			FText NodeName = NodeType.GetDefaultObject()->GetNodeName();
			
			TSharedPtr<FVGraphSchemaAction_NewNode> NewNodeSchemaAction = MakeShared<FVGraphSchemaAction_NewNode>(CreateCategory, NodeName, Tooltip, 0);
			NewNodeSchemaAction->SetTemplate(NodeType);
			ContextMenuBuilder.AddAction(NewNodeSchemaAction);
		}
	}
}

void UEdVGraphSchema::GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	const TAttribute<FText> Desc{LOCTEXT("ClassActionsMenuHeader", "Node Actions")};
	FToolMenuSection& Section = Menu->AddSection("VGraphAssetGraphSchemaNodeActions", Desc);
	Section.AddMenuEntry(FGenericCommands::Get().Delete);
	Section.AddMenuEntry(FGenericCommands::Get().Cut);
	Section.AddMenuEntry(FGenericCommands::Get().Copy);
	Section.AddMenuEntry(FGenericCommands::Get().Duplicate);
	Section.AddMenuEntry(FGraphEditorCommands::Get().BreakNodeLinks);
}

const FPinConnectionResponse UEdVGraphSchema::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	const UEdVNode* ABase = Cast<UEdVNode>(A->GetOwningNode());
	const UEdVNode* BBase = Cast<UEdVNode>(B->GetOwningNode());

	if (A->Direction == B->Direction)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Not allowed"));
	}

	if (A->PinType.PinCategory != B->PinType.PinCategory)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Not match types"));
	}

	if (ABase->GetUniqueID() == BBase->GetUniqueID())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Same node"));
	}

	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT(""));
}

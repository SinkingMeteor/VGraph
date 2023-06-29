// VGraph plugin copyright. All rights reserved.

#include "Slate/SVReplicaNode.h"
#include "Slate/SVBaseNode.h"
#include "EditorStyleSet.h"
#include "IDocumentation.h"
#include "SlateOptMacros.h"
#include "SLevelOfDetailBranchNode.h"
#include "GraphEditorSettings.h"
#include "SCommentBubble.h"
#include "Nodes/EdVNode.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SVReplicaNode::UpdateGraphNode()
{
	NodeInfoBlock.Reset();
	NodeInfoBlock = SNew(STextBlock);

	if(GraphNode)
	{
		UEdVNode* EdVNode = Cast<UEdVNode>(GraphNode);
		if(EdVNode)
		{
			NodeInfoBlock->SetText(EdVNode->GetNodeDisplayText());
		}
	}
	
	SGraphNode::UpdateGraphNode();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SVReplicaNode::CreateBelowWidgetControls(TSharedPtr<SVerticalBox> MainBox)
{
	MainBox->AddSlot()
	[
		SNew(SOverlay)
		+SOverlay::Slot()
		.Padding(Settings->GetNonPinNodeBodyPadding())
		[
			SNew(SImage)
			.Image(GetNodeBodyBrush())
			.ColorAndOpacity(this, &SGraphNode::GetNodeBodyColor)
		]
		+SOverlay::Slot()
		.Padding(5.0f, 5.0f, 2.0f, 2.0f)
		[
			NodeInfoBlock.ToSharedRef()
		]
	];
}

void SVReplicaNode::SetText(const FText& NewText)
{
	if(!NodeInfoBlock) return;
	
	NodeInfoBlock->SetText(NewText);
}

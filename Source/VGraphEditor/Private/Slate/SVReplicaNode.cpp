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
	NodeInfoBlock->SetWrappingPolicy(ETextWrappingPolicy::DefaultWrapping);
	NodeInfoBlock->SetAutoWrapText(true);
	
	if(!GraphNode)
	{
		SGraphNode::UpdateGraphNode();
		return;
	}

	const UEdVNode* EdVNode = CastChecked<UEdVNode>(GraphNode);
	SetFormattedTipText(EdVNode->GetNodeDisplayText());

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

void SVReplicaNode::SetText(const FText& NewText) const
{
	SetFormattedTipText(NewText);
}

const UVGraphEditorSettings* SVReplicaNode::GetEditorSettings() const
{
	const UEdVGraph* EdVGraph = CastChecked<UEdVGraph>(GraphNode->GetOuter());
	const UVGraphEditorSettings* EditorSettings = EdVGraph->GetEditorSettings();

	return EditorSettings;
}

void SVReplicaNode::SetFormattedTipText(const FText& Text) const
{
	if(!NodeInfoBlock) return;
	
	const UVGraphEditorSettings* EditorSettings = GetEditorSettings();
	check(EditorSettings)
	
	FString TipText = Text.ToString();

	const int32 MaxTipLength = EditorSettings->GetMaxTipLength();
	if(MaxTipLength < TipText.Len())
	{
		TipText = TipText.Mid(0, MaxTipLength);
	}
	
	NodeInfoBlock->SetText(FText::FromString(TipText));
}

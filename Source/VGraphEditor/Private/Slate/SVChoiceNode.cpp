// VGraph plugin copyright. All rights reserved.


#include "Slate/SVChoiceNode.h"

#include "GraphEditorSettings.h"
#include "SlateOptMacros.h"
#include "Nodes/EdVChoiceNode.h"
#include "Nodes/EdVNode.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SVChoiceNode::UpdateGraphNode()
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

	SetFormattedTipText();

	SGraphNode::UpdateGraphNode();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SVChoiceNode::CreateBelowWidgetControls(TSharedPtr<SVerticalBox> MainBox)
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

void SVChoiceNode::UpdateText() const
{
	SetFormattedTipText();
}

const UVGraphEditorSettings* SVChoiceNode::GetEditorSettings() const
{
	const UEdVGraph* EdVGraph = CastChecked<UEdVGraph>(GraphNode->GetOuter());
	const UVGraphEditorSettings* EditorSettings = EdVGraph->GetEditorSettings();

	return EditorSettings;
}

void SVChoiceNode::SetFormattedTipText() const
{
	const UVGraphEditorSettings* EditorSettings = GetEditorSettings();
	check(EditorSettings)

	const UEdVChoiceNode* EdVNode = CastChecked<UEdVChoiceNode>(GraphNode);
	const UVChoiceNode* ChoiceNode = Cast<UVChoiceNode>(EdVNode->VGraphNode);

	if(!ChoiceNode) return;

	const TArray<FDialogueChoice>& Choices = ChoiceNode->GetChoicesArray();

	FString TotalString{};
	
	for(int32 i = 0; i < Choices.Num(); ++i)
	{
		FString TipText = Choices[i].ChoiceText.ToString();
		
		const int32 MaxTipLength = EditorSettings->GetMaxTipLength();
		if(MaxTipLength < TipText.Len())
		{
			TipText = TipText.Mid(0, MaxTipLength);
		}

		TotalString.Append(TipText);
		TotalString.Append("\n");
	
	}
	
	NodeInfoBlock->SetText(FText::FromString(TotalString));
}
// VGraph plugin copyright. All rights reserved.


#include "Nodes/EdVChoiceNode.h"
#include "Slate/SVChoiceNode.h"

TSharedPtr<SGraphNode> UEdVChoiceNode::CreateSlateWidget()
{
	TSharedPtr<SVChoiceNode> Widget = SNew(SVChoiceNode, Cast<UEdVNode>(this));
	ChoiceWidget = Widget;
	return Widget;
}

void UEdVChoiceNode::OnPostChangedProperties()
{
	if(!ChoiceWidget.IsValid()) return;

	UVChoiceNode* ChoiceNode = Cast<UVChoiceNode>(VGraphNode);
	if(!ChoiceNode) return;

	const TArray<FDialogueChoice>& Choices = ChoiceNode->GetChoicesArray();
	const int32 TargetPinsNum = Choices.Num() + 1;

	TArray<FVGraphPinData> PinDataArray{};
	VGraphNode->GetPinData(PinDataArray);
	
	if(Pins.Num() > TargetPinsNum)
	{
		for (int32 i = TargetPinsNum; i < Pins.Num(); ++i)
		{
			if(Pins[i]->Direction == EEdGraphPinDirection::EGPD_Input) continue;
		
			if(RemovePin(Pins[i]))
			{
				--i;
			}
		}
	}

	const UEdVGraph* EdVGraph = CastChecked<UEdVGraph>(GetGraph());
	const UVGraphEditorSettings* EditorSettings = EdVGraph->GetEditorSettings();
	check(EditorSettings)
	const int32 MaxPinNameLength = EditorSettings->GetMaxPinNameLength();
	
	for (int32 i = 0; i < PinDataArray.Num(); ++i)
	{
		FString PinName = PinDataArray[i].PinName.ToString();
		if(MaxPinNameLength < PinName.Len())
		{
			PinName = PinName.Mid(0, MaxPinNameLength);
		}
		
		if(i >= Pins.Num())
		{
			CreatePin(EEdGraphPinDirection::EGPD_Output, "MultipleNodes", FName{}, FName{PinName});
			continue;
		}

		Pins[i]->PinName = FName{PinName};
	}

	ChoiceWidget.Pin()->UpdateGraphNode();
}

// VGraph plugin copyright. All rights reserved.


#include "Nodes/VChoiceNode.h"
#include "VDialogueParticipant.h"

#define LOCTEXT_NAMESPACE "VGraph_ChoiceNode"

FText UVChoiceNode::GetNodeName()
{
	return LOCTEXT("VGraph_ChoiceNode", "Choice Node");
}

FText UVChoiceNode::GetNodeDisplayText()
{
	if(DialogueParticipantData.IsValid())
	{
		const FText& ParticipantDisplayName = DialogueParticipantData.Get()->GetParticipantDisplayName();
		return FText::Format(LOCTEXT("VGraph_ChoiceNode_Title", "{0}"), ParticipantDisplayName);
	}
	
	return FText::GetEmpty();	
}

void UVChoiceNode::GetPinData(TArray<FVGraphPinData>& DataArray) const
{
	Super::GetPinData(DataArray);

	DataArray.Add(FVGraphPinData{ EEdGraphPinDirection::EGPD_Input, TEXT("In") });

	for(size_t i = 0; i < Choices.Num(); ++i)
	{
		const FName ChoiceName{Choices[i].ChoiceText.ToString()};
		DataArray.Add(FVGraphPinData{ EEdGraphPinDirection::EGPD_Output,  ChoiceName});
	}
}

UVBaseNode* UVChoiceNode::GetNextNode()
{
	return Super::GetNextNode();
}

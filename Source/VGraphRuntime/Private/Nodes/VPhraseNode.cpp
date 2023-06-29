// VGraph plugin copyright. All rights reserved.


#include "Nodes/VPhraseNode.h"

#define LOCTEXT_NAMESPACE "VGraph_PhraseNode"

FText UVPhraseNode::GetNodeName()
{
	return LOCTEXT("VGraph_PhraseNode", "Phrase Node");
}

FText UVPhraseNode::GetNodeDisplayText()
{
	if(DialogueParticipantData.IsValid())
	{
		const FText ParticipantDisplayName = DialogueParticipantData.Get()->GetParticipantDisplayName();
		return FText::Format(LOCTEXT("VGraph_PhraseNode_Title", "{0}: {1}"), ParticipantDisplayName, PhraseText);
	}
	
	return PhraseText;	
}

void UVPhraseNode::GetPinData(TArray<FVGraphPinData>& DataArray) const
{
	DataArray.Add(FVGraphPinData{ EEdGraphPinDirection::EGPD_Output, TEXT("Out") });
	DataArray.Add(FVGraphPinData{ EEdGraphPinDirection::EGPD_Input, TEXT("In") });
}

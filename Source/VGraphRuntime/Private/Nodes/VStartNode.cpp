// VGraph plugin copyright. All rights reserved.


#include "Nodes/VStartNode.h"

#define LOCTEXT_NAMESPACE "VGraph_StartNode"

FText UVStartNode::GetNodeName()
{
	return LOCTEXT("VGraph_StartNode", "Start Node");
}

void UVStartNode::GetPinData(TArray<FVGraphPinData>& DataArray) const
{
	DataArray.Add(FVGraphPinData{ EEdGraphPinDirection::EGPD_Output, TEXT("Out") });
}

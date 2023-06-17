// VGraph plugin copyright. All rights reserved.


#include "Nodes/VStartNode.h"

void UVStartNode::GetPinData(TArray<FVGraphPinData>& DataArray) const
{
	DataArray.Add(FVGraphPinData{ EEdGraphPinDirection::EGPD_Output, TEXT("Out") });
}

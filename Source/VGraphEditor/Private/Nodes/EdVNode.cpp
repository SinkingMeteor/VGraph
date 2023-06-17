// VGraph plugin copyright. All rights reserved.



#include "Nodes/EdVNode.h"
#include "Nodes/VBaseNode.h"

UEdVNode::UEdVNode()
{
	bCanRenameNode = true;
}

void UEdVNode::AllocateDefaultPins()
{
	check(VGraphNode)

	TArray<FVGraphPinData> PinDataArray{};
	VGraphNode->GetPinData(PinDataArray);

	for(const FVGraphPinData& PinData : PinDataArray)
	{
		CreatePin(PinData.Direction, "MultipleNodes", FName{}, PinData.PinName);
	}
}

FText UEdVNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if(!VGraphNode)
	{
		return Super::GetNodeTitle(TitleType);
	}

	return VGraphNode->GetNodeName();
}



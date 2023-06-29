// VGraph plugin copyright. All rights reserved.



#include "Nodes/EdVNode.h"
#include "Nodes/VBaseNode.h"

UEdVNode::UEdVNode()
{
	bCanRenameNode = true;
}

FLinearColor UEdVNode::GetNodeTitleColor() const
{
	if(!VGraphNode)
	{
		return Super::GetNodeTitleColor();
	}

	return VGraphNode->GetNodeTitleColor();
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
	return FText::FromString(GetAssetNodeType()->GetName());
}

FText UEdVNode::GetNodeDisplayText() const
{
	if(!VGraphNode) return GetNodeTitle(ENodeTitleType::FullTitle);
	return VGraphNode->GetNodeDisplayText();
}



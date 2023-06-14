// Snake Game


#include "Nodes/VGraphBaseNode.h"

UVGraphBaseNode::UVGraphBaseNode()
{
	bCanRenameNode = true;
}

void UVGraphBaseNode::AllocateDefaultPins()
{
	CreatePin(EEdGraphPinDirection::EGPD_Input, "MultipleNodes", FName{}, TEXT("In"));
	CreatePin(EEdGraphPinDirection::EGPD_Output, "MultipleNodes", FName{}, TEXT("Out"));
}



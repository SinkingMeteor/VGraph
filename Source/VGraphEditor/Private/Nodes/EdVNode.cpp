// Snake Game


#include "Nodes/EdVNode.h"

UEdVNode::UEdVNode()
{
	bCanRenameNode = true;
}

void UEdVNode::AllocateDefaultPins()
{
	CreatePin(EEdGraphPinDirection::EGPD_Input, "MultipleNodes", FName{}, TEXT("In"));
	CreatePin(EEdGraphPinDirection::EGPD_Output, "MultipleNodes", FName{}, TEXT("Out"));
}



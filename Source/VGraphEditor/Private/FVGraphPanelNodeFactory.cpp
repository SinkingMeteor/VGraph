// VGraph plugin copyright. All rights reserved.


#include "FVGraphPanelNodeFactory.h"

#include "Slate/SVBaseNode.h"


TSharedPtr<SGraphNode> FVGraphPanelNodeFactory::CreateNode(UEdGraphNode* Node) const
{
	UEdVNode* EdVNode = Cast<UEdVNode>(Node);
	if(!EdVNode) return nullptr;
	
	return EdVNode->CreateSlateWidget();
}

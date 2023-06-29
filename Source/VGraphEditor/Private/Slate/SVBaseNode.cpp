// VGraph plugin copyright. All rights reserved.


#include "Slate/SVBaseNode.h"
#include "GraphEditorSettings.h"
#include "Nodes/EdVNode.h"

void SVBaseNode::Construct(const FArguments& InArgs, UEdVNode* InEdVNode)
{
	GraphNode = InEdVNode;
	UpdateGraphNode();
}

bool SVBaseNode::IsNameReadOnly() const
{
	return SGraphNode::IsNameReadOnly();
}

bool SVBaseNode::UseLowDetailNodeTitles() const
{
	return SGraphNode::UseLowDetailNodeTitles();
}




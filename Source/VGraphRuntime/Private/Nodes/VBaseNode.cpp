// VGraph plugin copyright. All rights reserved.



#include "Nodes/VBaseNode.h"

UVBaseNode* UVBaseNode::GetNextNode()
{
	if(LinkedNodes.Num() == 0)
		return nullptr;

	return LinkedNodes[0];
}

void UVBaseNode::AddLinkedNode(UVBaseNode* LinkedNode)
{
	LinkedNodes.Add(LinkedNode);
}

void UVBaseNode::Clear()
{
	LinkedNodes.Empty();
}

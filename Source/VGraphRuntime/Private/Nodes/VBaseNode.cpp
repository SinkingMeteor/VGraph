// VGraph plugin copyright. All rights reserved.



#include "Nodes/VBaseNode.h"

void UVBaseNode::AddLinkedNode(UVBaseNode* LinkedNode)
{
	LinkedNodes.Add(LinkedNode);
}

void UVBaseNode::Clear()
{
	LinkedNodes.Empty();
}

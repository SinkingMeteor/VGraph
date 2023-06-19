// VGraph plugin copyright. All rights reserved.



#include "VGraph.h"

void UVGraph::AddNode(UVBaseNode* Node)
{
	Nodes.Add(Node);
}

void UVGraph::ClearGraph()
{
	StartNode = nullptr;
	Nodes.Empty();
}

// VGraph plugin copyright. All rights reserved.



#include "VGraph.h"

void UVGraph::AddNode(UVBaseNode* Node)
{
	Nodes.Add(Node);
}

void UVGraph::ClearGraph()
{
	StartNode = nullptr;

	for (UVBaseNode* Node : Nodes)
	{
		if(!Node) continue;
		
		Node->Clear();
	}
	
	Nodes.Empty();
}

bool UVGraph::IsValidGraph() const
{
	if(!StartNode) return false;
	if(Nodes.Num() == 0) return false;

	return true;
}

void UVGraph::Reset()
{
	CurrentNode = StartNode;
}

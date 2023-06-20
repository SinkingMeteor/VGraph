// VGraph plugin copyright. All rights reserved.

#include "EdVGraph.h"
#include "VGraph.h"

#include "Nodes/EdVNode.h"
#include "Nodes/VStartNode.h"

DEFINE_LOG_CATEGORY_STATIC(LogEdVGraph, All, All)

void UEdVGraph::RebuildGraph(UVGraph* TargetGraph)
{
	TargetGraph->ClearGraph();
	
	for(UEdGraphNode* EdNode : Nodes)
	{
		UEdVNode* VEdNode = Cast<UEdVNode>(EdNode);
		check(VEdNode)
		check(VEdNode->VGraphNode)

		for(UEdGraphPin* Pin : VEdNode->Pins)
		{
			for(UEdGraphPin* LinkedPin : Pin->LinkedTo)
			{
				if(!LinkedPin) continue;
				
				UVBaseNode* LinkedNode = Cast<UVBaseNode>(LinkedPin->GetOwningNode());
				if(!LinkedNode)
				{
					UE_LOG(LogEdVGraph, Warning, TEXT("Something went wrong when trying to get pin's owner"))
					continue;
				}
					
				VEdNode->VGraphNode->AddLinkedNode(LinkedNode);
			}
		}
		
		TargetGraph->AddNode(VEdNode->VGraphNode);

		if(VEdNode->VGraphNode->IsA<UVStartNode>())
		{
			if(TargetGraph->GetStartNode())
			{
				UE_LOG(LogEdVGraph, Warning, TEXT("Two or more start nodes was found. It's not supported"))
			}
			TargetGraph->SetStartNode(VEdNode->VGraphNode);
		}
	}
}

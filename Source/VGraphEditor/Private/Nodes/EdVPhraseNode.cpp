// VGraph plugin copyright. All rights reserved.


#include "Nodes/EdVPhraseNode.h"
#include "Slate/SVReplicaNode.h"

TSharedPtr<SGraphNode> UEdVPhraseNode::CreateSlateWidget()
{
	TSharedPtr<SVReplicaNode> Widget = SNew(SVReplicaNode, Cast<UEdVNode>(this));
	ReplicaWidget = Widget;
	return Widget;
}

void UEdVPhraseNode::OnPostChangedProperties()
{
	if(!ReplicaWidget.IsValid()) return;
	if(!VGraphNode) return;

	ReplicaWidget.Pin()->SetText(VGraphNode->GetNodeDisplayText());
}


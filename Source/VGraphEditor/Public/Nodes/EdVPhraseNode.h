// VGraph plugin copyright. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdVNode.h"
#include "Nodes/VPhraseNode.h"
#include "EdVPhraseNode.generated.h"

UCLASS()
class VGRAPHEDITOR_API UEdVPhraseNode : public UEdVNode
{
	GENERATED_BODY()
public:
	virtual TSubclassOf<UVBaseNode> GetAssetNodeType() const override { return UVPhraseNode::StaticClass(); }
	virtual TSharedPtr<SGraphNode> CreateSlateWidget() override;
	virtual void OnPostChangedProperties() override;
private:
	TWeakPtr<class SVReplicaNode> ReplicaWidget;
};

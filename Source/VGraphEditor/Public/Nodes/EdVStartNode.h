// VGraph plugin copyright. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdVNode.h"
#include "Nodes/VBaseNode.h"
#include "Nodes/EdVNode.h"
#include "Nodes/VStartNode.h"
#include "EdVStartNode.generated.h"

UCLASS()
class VGRAPHEDITOR_API UEdVStartNode : public UEdVNode
{
	GENERATED_BODY()
public:
	virtual TSubclassOf<UVBaseNode> GetAssetNodeType() const override { return UVStartNode::StaticClass(); }
};

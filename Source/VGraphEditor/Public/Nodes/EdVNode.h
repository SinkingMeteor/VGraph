// VGraph plugin copyright. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdVGraph.h"
#include "Nodes/VBaseNode.h"
#include "EdVNode.generated.h"

class UEdVGraph;

UCLASS()
class VGRAPHEDITOR_API UEdVNode : public UEdGraphNode
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UVBaseNode* VGraphNode;
	
	UEdVNode();
	virtual void AllocateDefaultPins() override;
	virtual bool GetCanRenameNode() const override { return true; }
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	UEdVGraph* GetVGraph() const { return Cast<UEdVGraph>(GetGraph()); }
};

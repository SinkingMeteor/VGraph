// Snake Game

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
	UEdVNode();
	virtual void AllocateDefaultPins() override;
	UEdVGraph* GetVGraph() const { return Cast<UEdVGraph>(GetGraph()); }
};

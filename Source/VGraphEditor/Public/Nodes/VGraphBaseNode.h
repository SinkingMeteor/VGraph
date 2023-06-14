// Snake Game

#pragma once

#include "CoreMinimal.h"
#include "EdVGraph.h"
#include "UObject/Object.h"
#include "VGraphBaseNode.generated.h"

class UEdVGraph;

UCLASS()
class VGRAPHEDITOR_API UVGraphBaseNode : public UEdGraphNode
{
	GENERATED_BODY()
public:
	UVGraphBaseNode();
	virtual void AllocateDefaultPins() override;
	UEdVGraph* GetVGraph() const { return Cast<UEdVGraph>(GetGraph()); }
};

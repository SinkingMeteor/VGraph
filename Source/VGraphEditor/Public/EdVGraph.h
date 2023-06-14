// Snake Game

#pragma once

#include "CoreMinimal.h"
#include "VGraph.h"
#include "EdVGraph.generated.h"

UCLASS()
class VGRAPHEDITOR_API UEdVGraph : public UEdGraph
{
	GENERATED_BODY()
public:
	void SetVGraph(UVGraph* InVGraph) { VGraph = InVGraph; }
	UVGraph* GetVGraph() const { return VGraph; }
private:
	UPROPERTY(VisibleAnywhere)
	UVGraph* VGraph;
};

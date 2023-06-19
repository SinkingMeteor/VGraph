// VGraph plugin copyright. All rights reserved.


#pragma once

#include "CoreMinimal.h"
#include "EdVGraph.generated.h"

UCLASS()
class VGRAPHEDITOR_API UEdVGraph : public UEdGraph
{
	GENERATED_BODY()
public:
	void RebuildGraph(class UVGraph* TargetGraph);
};

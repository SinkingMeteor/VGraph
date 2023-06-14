// Snake Game

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VBaseNode.generated.h"

class UVGraph;

UCLASS(Abstract)
class VGRAPHRUNTIME_API UVBaseNode : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UVGraph* ParentGraph;
};

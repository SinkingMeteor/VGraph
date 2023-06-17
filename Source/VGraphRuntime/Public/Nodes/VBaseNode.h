// Snake Game

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VBaseNode.generated.h"

class UVGraph;

#if WITH_EDITORONLY_DATA
class UEdGraphNode;
#endif

UCLASS(Abstract)
class VGRAPHRUNTIME_API UVBaseNode : public UObject
{
	GENERATED_BODY()

public:
	virtual FText GetNodeName() { return FText{}; }
	
private:
	UPROPERTY()
	UVGraph* ParentGraph;

#if WITH_EDITORONLY_DATA
public:
	UPROPERTY()
	UEdGraphNode* EditorNode;
#endif
};

// VGraph plugin copyright. All rights reserved.


#pragma once

#include "CoreMinimal.h"
#include "Nodes/VBaseNode.h"
#include "UObject/Object.h"
#include "VGraph.generated.h"

#if WITH_EDITORONLY_DATA
class UEdGraph;
#endif

UCLASS(Blueprintable)
class VGRAPHRUNTIME_API UVGraph : public UObject
{
	GENERATED_BODY()
public:
	void AddNode(UVBaseNode* Node);
private:
	UPROPERTY(Instanced)
	UVBaseNode* StartNode;
	UPROPERTY(Instanced)
	TArray<UVBaseNode*> Nodes;

#if WITH_EDITORONLY_DATA
public:
	UPROPERTY()
	UEdGraph* EditorGraph;
#endif
};

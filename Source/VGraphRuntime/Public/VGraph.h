// Snake Game

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

private:
	UPROPERTY(Instanced)
	TObjectPtr<UVBaseNode> StartNode;
	UPROPERTY(Instanced)
	TArray<TObjectPtr<UVBaseNode>> Nodes;

#if WITH_EDITORONLY_DATA
public:
	UEdGraph* GetEditorGraph() const { return EditorGraph; }
	UEdGraph*& GetEditorGraphRef() { return EditorGraph; }
	void SetEditorGraph(UEdGraph* InEditorGraph) { EditorGraph = InEditorGraph; }
private:
	UPROPERTY()
	UEdGraph* EditorGraph;
#endif

};

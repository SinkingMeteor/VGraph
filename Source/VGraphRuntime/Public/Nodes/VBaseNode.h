// Snake Game

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VBaseNode.generated.h"

#ifdef WITH_EDITORONLY_DATA
class UEdGraphNode;
#endif
class UVGraph;

UCLASS(Abstract)
class VGRAPHRUNTIME_API UVBaseNode : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UVGraph* ParentGraph;

#ifdef WITH_EDITORONLY_DATA
public:
	UEdGraphNode* GetEditorNode() const { return EditorNode; }
	void SetEditorNode(UEdGraphNode* InEditorNode) { EditorNode = InEditorNode; }
private:
	UEdGraphNode* EditorNode;
#endif
};

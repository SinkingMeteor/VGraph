// VGraph plugin copyright. All rights reserved.


#pragma once

#include "CoreMinimal.h"
#include "SGraphNode.h"
#include "UObject/Object.h"
#include "VBaseNode.generated.h"

class UVGraph;

#if WITH_EDITORONLY_DATA
class UEdGraphNode;
#endif

USTRUCT()
struct FVGraphPinData
{
	GENERATED_BODY()
public:
	EEdGraphPinDirection Direction;
	FName PinName;
};

UCLASS(Abstract)
class VGRAPHRUNTIME_API UVBaseNode : public UObject
{
	GENERATED_BODY()

public:
	virtual FText GetNodeName() { return FText::GetEmpty(); }
	virtual FText GetNodeTitle() { return GetNodeName(); }
	virtual void GetPinData(TArray<FVGraphPinData>& DataArray) const {}
	virtual void OnPropertiesChanged() {}
	virtual FLinearColor GetNodeTitleColor() { return FLinearColor::Gray; }
	virtual UVBaseNode* GetNextNode();
	virtual FSlateWidgetClassData GetNodeWidgetType() { return SGraphNode::StaticWidgetClass(); }
	void AddLinkedNode(UVBaseNode* LinkedNode);
	void Clear();
protected:
	UPROPERTY()
	TArray<UVBaseNode*> LinkedNodes; 
	UPROPERTY()
	UVGraph* ParentGraph;
};

// VGraph plugin copyright. All rights reserved.


#pragma once

#include "CoreMinimal.h"
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
	virtual FText GetNodeName() { return FText{}; }
	virtual void GetPinData(TArray<FVGraphPinData>& DataArray) const {}	
protected:
	UPROPERTY()
	UVGraph* ParentGraph;
};

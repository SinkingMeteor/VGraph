// VGraph plugin copyright. All rights reserved.


#pragma once

#include "CoreMinimal.h"
#include "VBaseNode.h"
#include "VStartNode.generated.h"

#define LOCTEXT_NAMESPACE "VGraph_StartNode"

UCLASS()
class VGRAPHRUNTIME_API UVStartNode : public UVBaseNode
{
	GENERATED_BODY()
public:
	virtual FText GetNodeName() override { return LOCTEXT("VGraph_StartNode", "Start Node"); }
	virtual void GetPinData(TArray<FVGraphPinData>& DataArray) const override;
};

// VGraph plugin copyright. All rights reserved.


#pragma once

#include "CoreMinimal.h"
#include "VBaseNode.h"
#include "VStartNode.generated.h"



UCLASS()
class VGRAPHRUNTIME_API UVStartNode : public UVBaseNode
{
	GENERATED_BODY()
public:
	virtual FText GetNodeName() override;
	virtual FLinearColor GetNodeTitleColor() override { return FLinearColor::Green; }
	virtual void GetPinData(TArray<FVGraphPinData>& DataArray) const override;
};

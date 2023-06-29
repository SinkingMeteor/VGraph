// VGraph plugin copyright. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "SGraphNode.h"

class VGRAPHEDITOR_API SVBaseNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SVBaseNode){}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, class UEdVNode* InEdVNode);
	virtual bool IsNameReadOnly() const override;
	virtual bool UseLowDetailNodeTitles() const override;
};

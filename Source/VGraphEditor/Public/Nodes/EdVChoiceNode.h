// VGraph plugin copyright. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdVNode.h"
#include "Nodes/VChoiceNode.h"
#include "EdVChoiceNode.generated.h"

UCLASS()
class VGRAPHEDITOR_API UEdVChoiceNode : public UEdVNode
{
	GENERATED_BODY()
public:
	virtual TSubclassOf<UVBaseNode> GetAssetNodeType() const override { return UVChoiceNode::StaticClass(); }
	virtual TSharedPtr<SGraphNode> CreateSlateWidget() override;
	virtual void OnPostChangedProperties() override;
private:
	TWeakPtr<class SVChoiceNode> ChoiceWidget;
};

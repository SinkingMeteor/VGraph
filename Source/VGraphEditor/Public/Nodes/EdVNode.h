// VGraph plugin copyright. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdVGraph.h"
#include "Nodes/VBaseNode.h"
#include "Slate/SVBaseNode.h"
#include "EdVNode.generated.h"

class UEdVGraph;

UCLASS(Abstract)
class VGRAPHEDITOR_API UEdVNode : public UEdGraphNode
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UVBaseNode* VGraphNode;
	
	UEdVNode();
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual void AllocateDefaultPins() override;
	virtual bool GetCanRenameNode() const override { return true; }
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetNodeDisplayText() const;
	UEdVGraph* GetVGraph() const { return Cast<UEdVGraph>(GetGraph()); }
	virtual TSharedPtr<SGraphNode> CreateSlateWidget() { return SNew(SVBaseNode, this); }

	//NEED TO IMPLEMENT
	virtual TSubclassOf<UVBaseNode> GetAssetNodeType() const { return nullptr; }
	//END NEED TO IMPLEMENT
	
	virtual void OnPostChangedProperties() {}
};

// Snake Game

#pragma once

#include "CoreMinimal.h"
#include "Nodes/VBaseNode.h"
#include "EdVGraphSchema.generated.h"

USTRUCT()
struct VGRAPHEDITOR_API FVGraphSchemaAction_NewNode : public FEdGraphSchemaAction
{
	GENERATED_BODY()

public:
	FVGraphSchemaAction_NewNode() = default;
	FVGraphSchemaAction_NewNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping, FText InKeywords = FText(), int32 InSectionID = 0);
	virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode) override;
	void SetTemplate(TSubclassOf<UVBaseNode> InNodeTemplate) { NodeTemplate = InNodeTemplate; }
private:
	 TSubclassOf<UVBaseNode> NodeTemplate;
};

UCLASS()
class VGRAPHEDITOR_API UEdVGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()
	
private:
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	virtual void GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;
	virtual EGraphType GetGraphType(const UEdGraph* TestEdGraph) const override { return EGraphType::GT_StateMachine; }
	virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override { return FColor::Yellow; }
	virtual bool ShouldHidePinDefaultValue(UEdGraphPin* Pin) const override { return true; }
	
};

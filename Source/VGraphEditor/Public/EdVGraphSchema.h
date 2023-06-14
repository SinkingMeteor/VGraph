// Snake Game

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EdVGraphSchema.generated.h"

UCLASS()
class VGRAPHEDITOR_API UEdVGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()
private:
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	virtual EGraphType GetGraphType(const UEdGraph* TestEdGraph) const override { return EGraphType::GT_StateMachine; }
};

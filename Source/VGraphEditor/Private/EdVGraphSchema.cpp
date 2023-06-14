// Snake Game


#include "EdVGraphSchema.h"

#define LOCTEXT_NAMESPACE "AssetSchema_VGraph"

void UEdVGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	Super::GetGraphContextActions(ContextMenuBuilder);

	TSharedPtr<FEdGraphSchemaAction_NewNode> NewNodeSchemaAction = MakeShared<FEdGraphSchemaAction_NewNode>(
		LOCTEXT("VGraphNodeAction_Category", "Create VGraph Node"),
		LOCTEXT("VGraphNodeAction_MenuDesc", "Create VGraph Node"),
		LOCTEXT("VGraphNodeAction_Tooltip", "Add here"), 0);
	ContextMenuBuilder.AddAction(NewNodeSchemaAction);
}

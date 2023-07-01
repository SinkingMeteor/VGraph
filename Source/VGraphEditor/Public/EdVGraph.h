// VGraph plugin copyright. All rights reserved.


#pragma once

#include "CoreMinimal.h"
#include "VGraphEditorSettings.h"
#include "EdVGraph.generated.h"

UCLASS()
class VGRAPHEDITOR_API UEdVGraph : public UEdGraph
{
	GENERATED_BODY()

public:
	void SetSettings(UVGraphEditorSettings* InEditorSettings) { EditorSettings = InEditorSettings; }
	const UVGraphEditorSettings* GetEditorSettings() const { return EditorSettings; }
	void RebuildGraph(class UVGraph* TargetGraph);
private:
	UPROPERTY()
	UVGraphEditorSettings* EditorSettings;
};

// VGraph plugin copyright. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "SVBaseNode.h"

class UVGraphEditorSettings;

class VGRAPHEDITOR_API SVChoiceNode : public SVBaseNode
{
public:
	virtual void UpdateGraphNode() override;
	virtual void CreateBelowWidgetControls(TSharedPtr<SVerticalBox> MainBox) override;
	void UpdateText() const;
private:
	TSharedPtr<STextBlock> NodeInfoBlock;

	const UVGraphEditorSettings* GetEditorSettings() const;
	void SetFormattedTipText() const;
};

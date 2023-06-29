// VGraph plugin copyright. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "SVBaseNode.h"

class VGRAPHEDITOR_API SVReplicaNode : public SVBaseNode
{
public:
	virtual void UpdateGraphNode() override;
	virtual void CreateBelowWidgetControls(TSharedPtr<SVerticalBox> MainBox) override;
	void SetText(const FText& NewText);
private:
	TSharedPtr<STextBlock> NodeInfoBlock;
};

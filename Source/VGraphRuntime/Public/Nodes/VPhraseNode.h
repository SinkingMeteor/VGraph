// VGraph plugin copyright. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "VBaseNode.h"
#include "VDialogueParticipant.h"
#include "UObject/Object.h"
#include "VPhraseNode.generated.h"


UCLASS()
class VGRAPHRUNTIME_API UVPhraseNode : public UVBaseNode
{
	GENERATED_BODY()
public:
	virtual FText GetNodeName() override;
	virtual FText GetNodeDisplayText() override;
	virtual FLinearColor GetNodeTitleColor() override { return FLinearColor::Blue; }
	virtual void GetPinData(TArray<FVGraphPinData>& DataArray) const override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue")
	TSoftObjectPtr<UVDialogueParticipant> DialogueParticipantData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue", meta=(MultiLine))
	FText PhraseText;
};

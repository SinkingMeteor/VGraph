// VGraph plugin copyright. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "VBaseNode.h"
#include "VChoiceNode.generated.h"

class UVDialogueParticipant;

USTRUCT(BlueprintType)
struct FDialogueChoice
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ChoiceText;
};

UCLASS()
class VGRAPHRUNTIME_API UVChoiceNode : public UVBaseNode
{
	GENERATED_BODY()
public:
	virtual FText GetNodeName() override;
	virtual FText GetNodeDisplayText() override;
	virtual FLinearColor GetNodeTitleColor() override { return FLinearColor::Yellow; }
	virtual void GetPinData(TArray<FVGraphPinData>& DataArray) const override;
	virtual UVBaseNode* GetNextNode() override;
	int32 GetChoicesNum() const { return Choices.Num();}
	const TArray<FDialogueChoice>& GetChoicesArray() const { return Choices;}
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue")
	TArray<FDialogueChoice> Choices;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue")
	TSoftObjectPtr<UVDialogueParticipant> DialogueParticipantData;
};

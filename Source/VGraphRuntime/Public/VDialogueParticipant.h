// VGraph plugin copyright. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VDialogueParticipant.generated.h"

UCLASS()
class VGRAPHRUNTIME_API UVDialogueParticipant : public UDataAsset
{
	GENERATED_BODY()
public:
	virtual const FName& GetParticipantName() { return ParticipantInternalName; }
	virtual const FText& GetParticipantDisplayName() { return DisplayName; }

protected:
	UPROPERTY(EditAnywhere, Category="Setup")
	FName ParticipantInternalName;
	UPROPERTY(EditAnywhere, Category="Setup")
	FText DisplayName;
};

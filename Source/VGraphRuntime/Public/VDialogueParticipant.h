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
	virtual FName GetParticipantName() { return FName{}; }
	virtual FText GetParticipantDisplayName() { return FText::GetEmpty(); }
};

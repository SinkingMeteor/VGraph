// VGraph plugin copyright. All rights reserved.


#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VGraphEditorSettings.generated.h"

/**
 * 
 */
UCLASS()
class VGRAPHEDITOR_API UVGraphEditorSettings : public UObject
{
	GENERATED_BODY()
public:
	int32 GetMaxTipLength() const { return MaxTipLength; }
protected:
	UPROPERTY(EditDefaultsOnly, Category="Visual")
	int32 MaxTipLength = 20;
};

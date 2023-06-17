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
	UPROPERTY(EditDefaultsOnly, Category="Test")
	float FooValue = 10.0f;
};

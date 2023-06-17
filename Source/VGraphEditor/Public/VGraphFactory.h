// VGraph plugin copyright. All rights reserved.


#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VGraphFactory.generated.h"

/**
 * 
 */
UCLASS()
class VGRAPHEDITOR_API UVGraphFactory : public UFactory
{
	GENERATED_BODY()
public:
	UVGraphFactory();
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};

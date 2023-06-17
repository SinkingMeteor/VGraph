// VGraph plugin copyright. All rights reserved.



#include "VGraphFactory.h"

#include "VGraph.h"

UVGraphFactory::UVGraphFactory()
{
	SupportedClass = UVGraph::StaticClass();
	bCreateNew = true;
}

UObject* UVGraphFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UVGraph>(InParent, InClass, InName, Flags, Context);
}

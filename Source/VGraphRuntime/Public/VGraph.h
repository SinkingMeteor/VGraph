// Snake Game

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VGraph.generated.h"

#if WITH_EDITORONLY_DATA
class UEdGraph;
#endif

UCLASS(Blueprintable)
class VGRAPHRUNTIME_API UVGraph : public UObject
{
	GENERATED_BODY()

public:
#if WITH_EDITORONLY_DATA
	UPROPERTY()
	class UEdGraph* EditorGraph;
#endif
	
};

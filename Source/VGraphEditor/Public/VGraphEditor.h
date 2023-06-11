// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VGraphAssetTypeActions.h"
#include "Modules/ModuleManager.h"

class FVGraphEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
private:
	TSharedPtr<FVGraphAssetTypeActions> GraphAssetTypeActions;
};

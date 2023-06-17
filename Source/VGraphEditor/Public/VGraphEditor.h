// VGraph plugin copyright. All rights reserved.


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

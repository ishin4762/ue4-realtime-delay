// Copyright (C) 2023 Broken Desk / ISHIN

#pragma once

#include "Modules/ModuleManager.h"

class FRealtimeDelayModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

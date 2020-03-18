// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FSimplePluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	void AddToolbarExtension(class FToolBarBuilder& Builder);
	void AddPullDownMenu(FMenuBarBuilder& MenuBuilder);
	void FillMenu(FMenuBuilder& MenuBuilder);
	void FillSubmenu(FMenuBuilder& MenuBuilder);

	void OnBtnClicked();

	TSharedPtr<FExtender> MyExtender;
	TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& TabSpawnArgs);


};

// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SimplePlugin.h"
#include "LevelEditor.h"
#include "SimplePluginCommands.h"
#include "EditorStyleSet.h"
#include "SDockTab.h"
#include "ContactWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogSimplePlugin, Log, All);

static const FName TabName("ClapTab");

void FSimplePluginModule::StartupModule()
{
	FSimplePluginCommands::Register();

	TSharedPtr<FUICommandList> MyPluginCommands = MakeShareable(new FUICommandList);

	MyPluginCommands->MapAction(
		FSimplePluginCommands::Get().Clap,
		FExecuteAction::CreateRaw(this, &FSimplePluginModule::OnBtnClicked),
		FCanExecuteAction());

	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	MyExtender = MakeShareable(new FExtender);
	MyExtender->AddToolBarExtension("Settings", EExtensionHook::After, MyPluginCommands
		, FToolBarExtensionDelegate::CreateRaw(this, &FSimplePluginModule::AddToolbarExtension));

	MyExtender->AddMenuBarExtension(
		"Help",
		EExtensionHook::After,
		MyPluginCommands,
		FMenuBarExtensionDelegate::CreateRaw(this, &FSimplePluginModule::AddPullDownMenu)
	);

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(MyExtender);
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MyExtender);

	TSharedRef<class FGlobalTabmanager> TabManager = FGlobalTabmanager::Get();
	TabManager->RegisterNomadTabSpawner(TabName, FOnSpawnTab::CreateRaw(this, &FSimplePluginModule::SpawnTab))
		.SetDisplayName(FText::FromString(TEXT("Clap")));
}

void FSimplePluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.GetToolBarExtensibilityManager()->RemoveExtender(MyExtender);
	LevelEditorModule.GetMenuExtensibilityManager()->RemoveExtender(MyExtender);

	FSimplePluginCommands::Unregister();

	TSharedRef<class FGlobalTabmanager> tm = FGlobalTabmanager::Get();
	tm->UnregisterNomadTabSpawner(TabName);

}

void FSimplePluginModule::AddToolbarExtension(class FToolBarBuilder& Builder)
{
#define LOCTEXT_NAMESPACE "LevelEditorToolBar"
	FSlateIcon IconBrush = FSlateIcon(FEditorStyle::GetStyleSetName()
		, "LevelEditor.ViewOptions", "LevelEditor.ViewOptions.Small");
	Builder.AddToolBarButton(FSimplePluginCommands::Get().Clap, NAME_None
		, LOCTEXT("MyButton_Override", "Clap"), LOCTEXT("MyButton_ToolTipOverride", "Click to clap"), IconBrush, NAME_None);
#undef LOCTEXT_NAMESPACE

}

void FSimplePluginModule::AddPullDownMenu(FMenuBarBuilder& MenuBuilder)
{
	MenuBuilder.AddPullDownMenu(
		FText::FromString("Menu Entry 1"),
		FText::FromString("Menu Entry 1 Tooltip"),
		FNewMenuDelegate::CreateRaw(this, &FSimplePluginModule::FillMenu),
		"Custom"
	);
}

void FSimplePluginModule::FillMenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.BeginSection("Clap");
	{

		MenuBuilder.AddMenuEntry(
			FSimplePluginCommands::Get().Clap, NAME_None,
			FText::FromString("Menu Entry 1"),
			FText::FromString("Menu Entry 1 Tooltip"),
			FSlateIcon()
		);
	}
	MenuBuilder.EndSection();

	MenuBuilder.BeginSection("Clap2");
	{

		// Create a Submenu inside of the Section
		MenuBuilder.AddSubMenu(FText::FromString("My Submenu"),
			FText::FromString("My submenu tooltip"),
			FNewMenuDelegate::CreateRaw(this, &FSimplePluginModule::FillSubmenu));
	}
	MenuBuilder.EndSection();

}

void FSimplePluginModule::FillSubmenu(FMenuBuilder& MenuBuilder)
{
	// Create the Submenu Entries

	MenuBuilder.AddMenuEntry(
		FSimplePluginCommands::Get().Clap2, NAME_None,
		FText::FromString("Menu Entry 1"),
		FText::FromString("Menu Entry 1 Tooltip"),
		FSlateIcon()
	);
}

void FSimplePluginModule::OnBtnClicked()
{
	UE_LOG(LogSimplePlugin, Log, TEXT("FSimplePluginModule::OnBtnClicked"));
	TSharedRef<class FGlobalTabmanager> tm = FGlobalTabmanager::Get();
	tm->InvokeTab(TabName);
}


TSharedRef<SDockTab> FSimplePluginModule::SpawnTab(const FSpawnTabArgs& TabSpawnArgs)
{
	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			[
				SNew(SContactWidget)

			]
			+ SHorizontalBox::Slot()
			[
				SNew(SButton)
				.Text(FText::FromString(TEXT("Clap")))
				.ContentPadding(3)
			]

		];

	return SpawnedTab;
}
	


IMPLEMENT_MODULE(FSimplePluginModule, SimplePlugin)

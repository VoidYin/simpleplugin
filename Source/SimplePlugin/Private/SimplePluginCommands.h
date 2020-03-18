#pragma once
#include "EditorStyleSet.h"
#include "Commands.h"

class  FSimplePluginCommands: public TCommands<FSimplePluginCommands>
{
	public:
	FSimplePluginCommands() : TCommands<FSimplePluginCommands>
	(
		"SimplePlugin", // Context name for fast lookup
		NSLOCTEXT("Contexts", "SimplePlugin", "SimplePlugin"), // Localized context name for displaying
		NAME_None, // Parent
		FEditorStyle::GetStyleSetName() // Icon Style Set
	)
	{
	}
	

	/**
	 * Initialize commands
	 */
	virtual void RegisterCommands() override;

public:
	
	TSharedPtr< FUICommandInfo > Clap;
	TSharedPtr< FUICommandInfo > Clap2;

};

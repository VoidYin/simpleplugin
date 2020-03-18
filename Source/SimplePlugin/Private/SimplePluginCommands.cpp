#include "SimplePluginCommands.h"
#define LOCTEXT_NAMESPACE "SimplePluginCommands"

void FSimplePluginCommands::RegisterCommands()
{
	UI_COMMAND(Clap, "Clap", "Clap hands", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(Clap2, "Clap2", "Clap hands", EUserInterfaceActionType::Button, FInputChord());

}

#undef LOCTEXT_NAMESPACE

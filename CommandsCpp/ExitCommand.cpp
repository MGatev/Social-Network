#include "ExitCommand.h"

void ExitCommand::execute(System& mySystem) {
	mySystem.exit();
}
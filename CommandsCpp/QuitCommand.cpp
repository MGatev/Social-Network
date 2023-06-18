#include "QuitCommand.h"

void QuitCommand::execute(System& mySystem) {
	mySystem.quit();
}
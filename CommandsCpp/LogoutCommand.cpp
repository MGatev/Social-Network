#include "LogoutCommand.h"

void LogoutCommand::execute(System& mySystem) {
	mySystem.logout();
}
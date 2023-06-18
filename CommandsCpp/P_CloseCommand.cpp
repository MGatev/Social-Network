#include "P_CloseCommand.h"

void P_CloseCommand::execute(System& mySystem) {
	mySystem.p_close();
}
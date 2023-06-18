#include "AboutCommand.h"

AboutCommand::AboutCommand(const size_t id) : id(id){}

void AboutCommand::execute(System& mySystem) {
	mySystem.about(id);
}
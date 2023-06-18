#include "UpVoteCommand.h"

UpVoteCommand::UpVoteCommand(const size_t id) : id(id) {}

void UpVoteCommand::execute(System& mySystem) {
	mySystem.upVote(id);
}
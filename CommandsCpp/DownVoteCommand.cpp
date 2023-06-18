#include "DownVoteCommand.h"

DownVoteCommand::DownVoteCommand(const size_t id) : id(id) {}

void DownVoteCommand::execute(System& mySystem) {
	mySystem.downVote(id);
}
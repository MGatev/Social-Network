#pragma once
#include "Command.h"

class UpVoteCommand : public Command
{
	size_t id;
public:
	UpVoteCommand(const size_t id);
	UpVoteCommand(const UpVoteCommand&) = delete;
	UpVoteCommand& operator=(const UpVoteCommand&) = delete;
	void execute(System& mySystem) override;
};
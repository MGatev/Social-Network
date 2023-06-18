#pragma once
#include "Command.h"

class DownVoteCommand : public Command
{
	size_t id;
public:
	DownVoteCommand(const size_t id);
	DownVoteCommand(const DownVoteCommand&) = delete;
	DownVoteCommand& operator=(const DownVoteCommand&) = delete;
	void execute(System& mySystem) override;
};
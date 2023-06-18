#pragma once
#include "Command.h"

class ExitCommand : public Command
{
public:
	ExitCommand() = default;
	ExitCommand(const ExitCommand&) = delete;
	ExitCommand& operator=(const ExitCommand&) = delete;
	void execute(System& mySystem) override;
};
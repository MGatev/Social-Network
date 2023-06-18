#pragma once

#include "Command.h"

class LogoutCommand : public Command
{
public:
	LogoutCommand() = default;
	LogoutCommand(const LogoutCommand&) = delete;
	LogoutCommand& operator=(const LogoutCommand&) = delete;
	void execute(System& mySystem) override;
};
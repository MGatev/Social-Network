#pragma once

#include "Command.h"

class QuitCommand : public Command
{
public:
	QuitCommand() = default;
	QuitCommand(const QuitCommand&) = delete;
	QuitCommand& operator=(const QuitCommand&) = delete;
	void execute(System& mySystem) override;
};
#pragma once

#include "Command.h"

class DisplayCommentsCommand : public Command
{
public:
	DisplayCommentsCommand() = default;
	DisplayCommentsCommand(const DisplayCommentsCommand&) = delete;
	DisplayCommentsCommand& operator=(const DisplayCommentsCommand&) = delete;
	void execute(System& mySystem) override;
};
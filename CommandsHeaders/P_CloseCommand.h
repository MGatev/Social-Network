#pragma once
#include "Command.h"

class P_CloseCommand : public Command
{
public:
	P_CloseCommand() = default;
	P_CloseCommand(const P_CloseCommand&) = delete;
	P_CloseCommand& operator=(const P_CloseCommand&) = delete;
	void execute(System& mySystem) override;
};
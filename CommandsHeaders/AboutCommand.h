#pragma once
#include "Command.h"

class AboutCommand : public Command
{
	size_t id;
public:
	AboutCommand(const size_t id);
	AboutCommand(const AboutCommand&) = delete;
	AboutCommand& operator=(const AboutCommand&) = delete;
	void execute(System& mySystem) override;
};
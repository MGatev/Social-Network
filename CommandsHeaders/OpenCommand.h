#pragma once
#include "Command.h"

class OpenCommand : public Command
{
	MyString fullName;
public:
	OpenCommand(const MyString& fullName);
	OpenCommand(const OpenCommand&) = delete;
	OpenCommand& operator=(const OpenCommand&) = delete;
	void execute(System& mySystem) override;
};
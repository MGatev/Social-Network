#pragma once
#include "Command.h"

class P_OpenCommand : public Command
{
	MyString fullName;
public:
	P_OpenCommand(const MyString& fullName);
	P_OpenCommand(const P_OpenCommand&) = delete;
	P_OpenCommand& operator=(const P_OpenCommand&) = delete;
	void execute(System& mySystem) override;
};
#pragma once
#include "Command.h"

class LoginCommand : public Command
{
	MyString firstName;
	MyString password;
public:
	LoginCommand(const MyString& firstName, const MyString& password);
	LoginCommand(const LoginCommand&) = delete;
	LoginCommand& operator=(const LoginCommand&) = delete;
	void execute(System& mySystem) override;
};

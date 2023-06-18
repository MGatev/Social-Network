#pragma once
#include "Command.h"

class SignUpCommand : public Command
{
	MyString firstName;
	MyString lastName;
	MyString password;
public:
	SignUpCommand(const MyString& firstName, const MyString& lastName, const MyString& password);
	SignUpCommand(const SignUpCommand&) = delete;
	SignUpCommand& operator=(const SignUpCommand&) = delete;
	void execute(System& mySystem) override;
};
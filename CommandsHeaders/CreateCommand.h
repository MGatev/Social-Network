#pragma once
#include "Command.h"

class CreateCommand : public Command
{
	MyString title;
	MyString description;
public:
	CreateCommand(const MyString& title, const MyString& description);
	CreateCommand(const CreateCommand&) = delete;
	CreateCommand& operator=(const CreateCommand&) = delete;
	void execute(System& mySystem) override;
};
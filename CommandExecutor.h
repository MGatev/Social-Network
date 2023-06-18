#pragma once
#include "Command.h"
#include "System.h"
#include "ExitCommand.h"

class CommandExecutor
{
	Command* arr[5];
	size_t size = 0;
	System mySystem;

	void executeAll();
public:
	CommandExecutor();
	CommandExecutor(const CommandExecutor&) = delete;
	CommandExecutor& operator=(const CommandExecutor&) = delete;
	void addCommand(Command* command);
	~CommandExecutor();
};
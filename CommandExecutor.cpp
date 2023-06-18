#include "CommandExecutor.h"

CommandExecutor::CommandExecutor():arr(), mySystem() {
	mySystem.printInstructions();
	mySystem.readFromFile();
}

void CommandExecutor::executeAll()
{
	for (int i = 0; i < size; i++)
	{
		arr[i]->execute(mySystem);
		delete arr[i];
	}
	size = 0;
}

void CommandExecutor::addCommand(Command* command)
{
	
	arr[size++] = command;
	if (size == 1)
		executeAll();
}

CommandExecutor::~CommandExecutor()
{
	executeAll();
}
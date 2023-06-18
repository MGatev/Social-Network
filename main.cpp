#include <iostream>
#include "CommandExecutor.h"
#include "CommandFactory.h"

int main()
{
 	CommandExecutor ex;

	while (true)
	{
		ex.addCommand(CommandFactory::getInstance().getCommand());
	}

	return 0;
}
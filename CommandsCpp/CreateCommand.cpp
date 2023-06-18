#include "CreateCommand.h"

CreateCommand::CreateCommand(const MyString& title, const MyString& description) :
	title(title), description(description)
{}

void CreateCommand::execute(System& mySystem) {
	mySystem.createTopic(title, description);
}
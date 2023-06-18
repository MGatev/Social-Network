#include "loginCommand.h"

LoginCommand::LoginCommand(const MyString& firstName, const MyString& password):
	firstName(firstName), password(password)
{}

void LoginCommand::execute(System& mySystem) {
	mySystem.login(firstName, password);
}


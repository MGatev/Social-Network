#include "signUpCommand.h"

SignUpCommand::SignUpCommand(const MyString& firstName, const MyString& lastName, const MyString& password) :
				   firstName(firstName), lastName(lastName), password(password)
{}

void SignUpCommand::execute(System& mySystem)
{
	mySystem.signUp(firstName, lastName, password);
}
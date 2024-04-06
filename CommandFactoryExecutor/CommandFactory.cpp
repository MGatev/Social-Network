#include "CommandFactory.h"
#include "SignUpCommand.h"
#include "LoginCommand.h"
#include "SearchCommand.h"
#include "CommentCommand.h"
#include "CreateCommand.h"
#include "PostCommand.h"
#include "ListCommand.h"
#include "OpenCommand.h"
#include "P_OpenCommand.h"
#include "ReplyCommand.h"
#include "P_CloseCommand.h"
#include "QuitCommand.h"
#include "WhoAmICommand.h"
#include "AboutCommand.h"
#include "UpVoteCommand.h"
#include "DownVoteCommand.h"
#include "DisplayCommentsCommand.h"
#include "ExitCommand.h"
#include "LogoutCommand.h"
#include <stdexcept>
#include <iostream>
#include <sstream>


Command* CommandFactory::getCommand() const
{
	MyString userInput;
	std::cin >> userInput;
	std::cin.ignore();
	
	try
	{
		if (strcmp(userInput.c_str(), "signup") == 0)
		{

			MyString firstName, lastName, password;
			std::cout << "Please enter your first name: ";
			std::cin >> firstName;
			std::cout << "\n" << "Please enter your last name: ";
			std::cin >> lastName;
			std::cout << "\n" << "Please enter your password: ";
			std::cin >> password;
			return new SignUpCommand(firstName, lastName, password);
		}
		else if (strcmp(userInput.c_str(), "login") == 0)
		{
			MyString firstName, password;
			std::cout << "Please enter your first name: ";
			std::cin >> firstName;
			std::cout << "\n" << "Please enter your password: ";
			std::cin >> password;
			return new LoginCommand(firstName, password);
		}
		else if (strcmp(userInput.c_str(), "search") == 0)
		{
			char buff[500];
			std::cin.getline(buff, 500);
			MyString keyWord(buff);
			return new SearchCommand(keyWord);
		}
		else if (strcmp(userInput.c_str(), "create") == 0)
		{
			char buff[500];

			std::cout << "Enter a title: ";
			std::cin.getline(buff, 500); //read title
			MyString title(buff);

			std::cout << "\nEnter a short description: ";
			std::cin.getline(buff, 500);//read description
			MyString description(buff);

			return new CreateCommand(title, description);
		}
		else if (strcmp(userInput.c_str(), "open") == 0)
		{
			char buff[500];
			std::cin.getline(buff, 500);
			MyString fullName(buff);
			return new OpenCommand(fullName);
		}
		else if (strcmp(userInput.c_str(), "list") == 0)
		{
			return new ListCommand();
		}
		else if (strcmp(userInput.c_str(), "post") == 0)
		{
			char buff[500];

			std::cout << "Enter a title: ";
			std::cin.getline(buff, 500); //read title
			MyString title(buff);

			std::cout << "\nEnter a short description: ";
			std::cin.getline(buff, 500);//read description
			MyString description(buff);

			return new PostCommand(Question(title, description));

		}
		else if (strcmp(userInput.c_str(), "p_open") == 0)
		{
			char buff[500];
			std::cin.getline(buff, 500);
			MyString fullName(buff);
			return new P_OpenCommand(fullName);
		}
		else if (strcmp(userInput.c_str(), "comment") == 0)
		{
			char buff[500];

			std::cout << "Enter a comment: ";
			std::cin.getline(buff, 500); //read title
			MyString newComment(buff);

			return new CommentCommand(newComment);
		}
		else if (strcmp(userInput.c_str(), "reply") == 0) {
			size_t idToComment = 0;
			std::cin >> idToComment;
			std::cin.ignore();

			char buff[500];

			std::cout << "Enter a reply: ";
			std::cin.getline(buff, 500); //read title
			MyString newReply(buff);

			std::cout << "\nEnter a creator: ";
			std::cin.getline(buff, 500);//read description
			MyString creator(buff);

			return new ReplyCommand(creator, newReply, idToComment);
		}
		else if (strcmp(userInput.c_str(), "p_close") == 0) {
			return new P_CloseCommand();
		}
		else if (strcmp(userInput.c_str(), "quit") == 0) {
			return new QuitCommand();
		}
		else if (strcmp(userInput.c_str(), "whoami") == 0) {
			return new WhoAmICommand();
		}
		else if (strcmp(userInput.c_str(), "about") == 0) {
			size_t idToSeeInfo = 0;
			std::cin >> idToSeeInfo;
			std::cin.ignore();

			return new AboutCommand(idToSeeInfo);
		}
		else if (strcmp(userInput.c_str(), "upvote") == 0) {
			size_t userID = 0;
			std::cin >> userID;
			std::cin.ignore();

			return new UpVoteCommand(userID);
		}
		else if (strcmp(userInput.c_str(), "downvote") == 0) {
			size_t userID = 0;
			std::cin >> userID;
			std::cin.ignore();

			return new DownVoteCommand(userID);
		}
		else if (strcmp(userInput.c_str(), "comments") == 0) {
			return new DisplayCommentsCommand();
		}
		else if (strcmp(userInput.c_str(), "logout") == 0) {
			return new LogoutCommand();
		}
		else if (strcmp(userInput.c_str(), "exit") == 0) {
			return new ExitCommand();
		}
		else {
			throw std::invalid_argument("Invalid Command!");
		}
	}
	catch (const std::invalid_argument&)
	{
		std::cout << "Invalid command! Try again!" << std::endl;
		Command* commandToReturn = getCommand();
		return commandToReturn;
	}
	


}

CommandFactory& CommandFactory::getInstance()
{
	static CommandFactory factory;
	return factory;
}

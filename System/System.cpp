#include "System.h"
#include "Constants.h"

namespace {
	int check_substring(const MyString& str1, const MyString& str2)
	{
		int i, j;
		int len1 = static_cast<int>(str1.length());
		int len2 = static_cast<int>(str2.length());

		for (i = 0; i <= len2 - len1; i++) {
			for (j = 0; j < len1; j++)
				if (str2[i + j] != str1[j])
					break;

			if (j == len1)
				return i;
		}

		return -1;
	}

template <typename T>
	int getPositionInArr(const Collection<T>& arr, const size_t id) {
		for (int i = 0; i < arr.getTCount(); i++)
		{
			if (arr[i].getID() == id)
				return i;
		}
		return -1;
	}
}

void System::printInstructions()const {
	std::cout << "Hello, these are the commands which you can use to navigate through the system: " <<std::endl
		<< " -> signup - to create an account" << std::endl << " -> login - to log into your account"
		<< std::endl << " -> create - to create a new topic" << std::endl
		<< " -> search <keyWord> - to search for a topic containing the keyWord" << std::endl
		<< " -> about <id> - to see the information about a topic by its id" << std::endl
		<< " -> open <id>/<full topic name> - to open a topic by its id or by the full name of the topic"
		<< std::endl << " -> list - to show all questions in a topic" << std::endl
		<< " -> p_open <id>/<fullPostName - to open a question by its id or the full post name"
		<< std::endl << " -> post - to post a question in a topic" << std::endl
		<< " -> comment - to comment under a question" << std::endl
		<< " -> comments - to see all the comments in a question" << std::endl
		<< " -> reply <id> - to reply to a question using its id" << std::endl
		<< " -> upvote <id> - to like a comment or a reply by its id" << std::endl
		<< " -> downvote <id> - to dislike a comment or reply by its id" << std::endl
		<< " -> p_close - closes the question you are in" << std::endl
		<< " -> quit - closes the topic you are in" << std::endl
		<< " -> whoami - to see your personal information" << std::endl
		<< " -> logout - logouts of your account" << std::endl
		<< " -> exit - to exit the system"<<std::endl<<std::endl;
}

bool System::signUp(const MyString& firstName, const MyString& lastName, const MyString& password) {
	if (userLoggedIn >= 0) {
		std::cout << "You are logged in. Please logout!" << std::endl;
		return false;
	}

	users.addT(User(firstName, lastName, password));
	std::cout << "You signed in successfully!\n";

	return true;
}

bool System::login(const MyString& firstName, const MyString& password) const {
	if (userLoggedIn >= 0) {
		std::cout << "You have already logged in!" << std::endl;
		return false;
	}
		
	for (size_t i = 0; i < users.getTCount(); i++)
	{
		if (users.getTByIndex(i).getFirstName() == firstName)
		{
			if (users.getTByIndex(i).getPassword() == password)
			{
				userLoggedIn = static_cast<int>(i);
				users[i].changeIsLoggedIn();
				std::cout << "You have logged in successfully!\n";
				return true;
			}
		}
	}
	std::cout << "You entered incorrect name or password! Try again!\n";
	return false;
}

bool System::search(const MyString& keyWord)const {
	if (userLoggedIn < 0) {
		std::cout << "You are not logged in! Please log in first." << std::endl;
		return false;
	}

	bool isFound = false;

	for (size_t i = 0; i < topics.getTCount(); i++)
	{
		if (check_substring(keyWord, topics.getTByIndex(i).getTitle()) >= 0)
		{
			isFound = true;
			std::cout << " - ";
			topics.getTByIndex(i).printTopic();
		}
	}

	if (isFound == false)
	{
		std::cout << "There aren't any topics containing " << keyWord << std::endl;
		return false;
	}


	return true;
}

bool System::createTopic(const MyString& title, const MyString& description) {
	if (userLoggedIn < 0) {
		std::cout << "You are not logged in! Please log in first." << std::endl;
		return false;
	}
	topics.addT(Topic(title, description, users[userLoggedIn].getFirstName()));
	std::cout << "You have successfully created a new topic!" << std::endl;
	return true;
}

bool System::open(const MyString& fullName) {
	if (userLoggedIn < 0) {
		std::cout << "You are not logged in! Please log in first." << std::endl;
		return false;
	}
	if (openedTopic >= 0 && openedQuestion >= 0) {
		topics[openedTopic].getQuestions()[openedQuestion].changeIsOpen();
		openedQuestion = -1;
	}

	for (size_t i = 0; i < topics.getTCount(); i++)
	{
		if (topics.getTByIndex(i).getTitle() == fullName)
		{
			openedTopic = static_cast<int>(i);
			Topic changedTopic = topics.getTByIndex(i);
			changedTopic.changeIsOpen();
			topics.setTByIndex(changedTopic, i);
			std::cout << "Welcome to '" << topics.getTByIndex(i).getTitle() << "'!\n";
			return true;
		}
	}

	std::cout << "Invalid name! There aren't any topics containing " << fullName << std::endl;
	return false;
}

bool System::open(const size_t idNumber) {
	if (userLoggedIn < 0) {
		std::cout << "You are not logged in! Please log in first." << std::endl;
		return false;
	}
	if (openedTopic >= 0 && openedQuestion >= 0) {
		topics[openedTopic].getQuestions()[openedQuestion].changeIsOpen();
		openedQuestion = -1;
	}

	for (size_t i = 0; i < topics.getTCount(); i++)
	{
		if (topics.getTByIndex(i).getId() == idNumber)
		{
			openedTopic = static_cast<int>(i);
			Topic changedTopic = topics.getTByIndex(i);
			changedTopic.changeIsOpen();
			topics.setTByIndex(changedTopic, i);
			std::cout << "Welcome to '" << topics.getTByIndex(i).getTitle() << "'!\n";
			return true;
		}
	}
	std::cout << "There aren't any topics with the id " << idNumber << std::endl;
	return false;
}

bool System::p_open(const size_t questionId){
	if (userLoggedIn < 0) {
		std::cout << "You are not logged in! Please log in first." << std::endl;
		return false;
	}
	if (openedTopic < 0) {
		std::cout << "You havent opened a Topic! Please open one first" << std::endl;
		return false;
	}
	
	for (size_t i = 0; i < topics.getTByIndex(openedTopic).getQuestions().getTCount(); i++) {
		if (topics.getTByIndex(openedTopic).getQuestions()[i].getId() == questionId)
		{
			openedQuestion = static_cast<int>(i);
			topics.getTByIndex(openedTopic).getQuestions()[i].changeIsOpen();
			
			comments();

			return true;
		}
	}

	std::cout << "There aren't any questions with the id " << questionId << std::endl;
	return false;
}

bool System::p_open(const MyString& title) {
	if (userLoggedIn < 0) {
		std::cout << "You are not logged in! Please log in first." << std::endl;
		return false;
	}
	if (openedTopic < 0) {
		std::cout << "You havent opened a Topic! Please open one first" << std::endl;
		return false;
	}

	
	for (size_t i = 0; i < topics.getTByIndex(openedTopic).getQuestions().getTCount(); i++) {
		if (topics.getTByIndex(openedTopic).getQuestions()[i].getTitle() == title)
		{
			openedQuestion = static_cast<int>(i);
			topics.getTByIndex(openedTopic).getQuestions()[i].changeIsOpen();
			
			comments();

			return true;
		}
	}
	std::cout << "Invalid name! There aren't any questions called " << title << std::endl;
	return false;
}

bool System::list()const {
	if (openedTopic < 0) {
		std::cout << "First you need to open a topic!\n";
		return false;
	}

	if (topics[openedTopic].getQuestions().getTCount() == 0)
	{
		std::cout << "There aren't any questions in this topic at the moment!" << std::endl;
		return true;
	}

	for (size_t i = 0; i < topics[openedTopic].getQuestions().getTCount(); i++)
	{
		topics[openedTopic].getQuestions()[i].printQuestion();
	}

	return true;

}

bool System::comments()const {
	if (userLoggedIn < 0)
	{
		std::cout << "First you need to log in!\n";
		return false;
	}
	if (openedTopic < 0) {
		std::cout << "First you need to open a topic!\n";
		return false;
	}
	if (openedQuestion < 0)
	{
		std::cout << "First you need to open a question!\n";
		return false;
	}

	if (topics[openedTopic].getQuestions()[openedQuestion].getComments().getTCount() == 0) {
		std::cout << "There aren't any comments in this section at the moment." << std::endl;
		return true;
	}

	for (size_t i = 0; i < topics[openedTopic].getQuestions()[openedQuestion].getComments().getTCount(); i++)
	{
		topics[openedTopic].getQuestions()[openedQuestion].getComments()[i].printComment();
	}

	return true;
}

bool System::post(const Question& questionToPost) {
	if (openedTopic < 0) {
		std::cout << "First you need to open a topic!\n";
		return 0;
	}

	topics[openedTopic].addQuestion(questionToPost);
	return true;
}

bool System::comment(const MyString& newComment) {
	if (userLoggedIn < 0)
	{
		std::cout << "First you need to log in!\n";
		return false;
	}
	if (openedTopic < 0) {
		std::cout << "First you need to open a topic!\n";
		return false;
	}
	if (openedQuestion < 0)
	{
		std::cout << "First you need to open a question!\n";
		return false;
	}
	Comment commentToAdd(users[userLoggedIn].getFirstName(), newComment);

	topics.getTByIndex(openedTopic).getQuestions().getTByIndex(openedQuestion).
		addComment(std::move(commentToAdd));

	return true;
}

bool System::reply(const size_t id, const MyString& creator, const MyString& newReply) {
	if (userLoggedIn < 0)
	{
		std::cout << "First you need to log in!\n";
		return false;
	}
	if (openedTopic < 0) {
		std::cout << "First you need to open a topic!\n";
		return false;
	}
	if (openedQuestion < 0)
	{
		std::cout << "First you need to open a question!\n";
		return false;
	}
	Comment replyToAdd(creator, newReply);

	int commentPos = getPositionInArr(topics.getTByIndex(openedTopic).getQuestions().getTByIndex(openedQuestion).
		getComments(), id);
	if (commentPos < 0) {
		std::cout << "You have ented an invalid ID!" << std::endl;
		return false;
	}

	topics[openedTopic].getQuestions()[openedQuestion].
		   getComments()[commentPos].getReplies().addT(std::move(replyToAdd));

	return true;
}

bool System::logout() {
	if (userLoggedIn < 0) {
		std::cout << "You are not logged in!" << std::endl;
		return 0;
	}

	if (openedQuestion >= 0) {
		topics[openedTopic].getQuestions()[openedQuestion].changeIsOpen();
		openedQuestion = -1;
	}

	if (openedTopic >= 0) {
		topics[openedTopic].changeIsOpen();
		openedTopic = -1;
	}
		

	users[userLoggedIn].changeIsLoggedIn();
	userLoggedIn = -1;
	std::cout << "You logged out of your profile!" << std::endl;
	return 1;
}

bool System::p_close() {
	if (userLoggedIn < 0)
	{
		std::cout << "First you need to log in!\n";
		return false;
	}
	if (openedTopic < 0) {
		std::cout << "First you need to open a topic!\n";
		return false;
	}
	if (openedQuestion < 0)
	{
		std::cout << "You havent opened a question!\n";
		return false;
	}
	topics[openedTopic].getQuestions()[openedQuestion].changeIsOpen();
	openedQuestion = -1;
	return true;
}

bool System::quit() {
	if (userLoggedIn < 0)
	{
		std::cout << "First you need to log in!\n";
		return false;
	}
	if (openedTopic < 0) {
		std::cout << "First you need to open a topic!\n";
		return false;
	}
		
	if (openedQuestion >= 0)
	{
		topics[openedTopic].getQuestions()[openedQuestion].changeIsOpen();
		openedQuestion = -1;
	}
	topics[openedTopic].changeIsOpen();
	openedTopic = -1;
	return true;
}

bool System::whoAmI()const {
	if (userLoggedIn < 0) {
		std::cout << "You havent logged in!" << std::endl;
		return 0;
	}

	users[userLoggedIn].printUser();
	return true;
}

bool System::about(const size_t id)const {
	int topicPlace = -1;
	for (size_t i = 0; i < topics.getTCount(); i++)
	{
		if (topics[i].getId() == id) {
			topicPlace = static_cast<int>(i);
			break;
		}	
	}
	if (topicPlace < 0) {
		std::cout << "Invalid ID!" << std::endl;
		return false;
	}

	topics[topicPlace].printTopic();
	return true;
}

bool System::upVote(const size_t id) {
	if (userLoggedIn >= 0 && openedTopic >= 0 && openedQuestion >= 0) {

		int commentPos = getPositionInArr(topics.getTByIndex(openedTopic).getQuestions().
			getTByIndex(openedQuestion).getComments(), id);

		if (commentPos < 0)
		{
			std::cout << "Incorrect id!" << std::endl;
			return false;
		}

		if (topics[openedTopic].getQuestions()[openedQuestion].getComments()[commentPos]
			.isAlreadyUpVoted(userLoggedIn))
		{
			topics[openedTopic].getQuestions()[openedQuestion].getComments()[commentPos]
				.removeUpVote(userLoggedIn);
			int tempPoints = users[userLoggedIn].getPoints() - 1;
			users[userLoggedIn].setPoints(tempPoints);
			return true;
		}	
		else if (topics[openedTopic].getQuestions()[openedQuestion].getComments()[commentPos]
			.isAlreadyDownVoted(userLoggedIn))
		{
			topics[openedTopic].getQuestions()[openedQuestion].getComments()[commentPos]
				.removeDownVote(userLoggedIn);
			topics[openedTopic].getQuestions()[openedQuestion].
				getComments()[commentPos].addUpVote(userLoggedIn);
			return true;
		}
		else
		{
			topics[openedTopic].getQuestions()[openedQuestion].
				getComments()[commentPos].addUpVote(userLoggedIn);
			int tempPoints = users[userLoggedIn].getPoints() + 1;
			users[userLoggedIn].setPoints(tempPoints);
			return true;
		}
		
	}

	return false;
}

bool System::downVote(const size_t id) {
	if (userLoggedIn >= 0 && openedTopic >= 0 && openedQuestion >= 0) {

		int commentPos = getPositionInArr(topics.getTByIndex(openedTopic).getQuestions().
			getTByIndex(openedQuestion).getComments(), id);

		if (commentPos < 0)
		{
			std::cout << "Incorrect id!" << std::endl;
			return false;
		}

		if (topics[openedTopic].getQuestions()[openedQuestion].getComments()[commentPos]
			.isAlreadyDownVoted(userLoggedIn))
		{
			topics[openedTopic].getQuestions()[openedQuestion].getComments()[commentPos]
				.removeDownVote(userLoggedIn);
			int tempPoints = users[userLoggedIn].getPoints() - 1;
			users[userLoggedIn].setPoints(tempPoints);
			return true;
		}
		else if (topics[openedTopic].getQuestions()[openedQuestion].getComments()[commentPos]
			.isAlreadyUpVoted(userLoggedIn))
		{
			topics[openedTopic].getQuestions()[openedQuestion].getComments()[commentPos]
				.removeUpVote(userLoggedIn);
			topics[openedTopic].getQuestions()[openedQuestion].
				getComments()[commentPos].addDownVote(userLoggedIn);
			return true;
		}
		else
		{
			topics[openedTopic].getQuestions()[openedQuestion].
				getComments()[commentPos].addDownVote(userLoggedIn);
			int tempPoints = users[userLoggedIn].getPoints() + 1;
			users[userLoggedIn].setPoints(tempPoints);
			return true;
		}
	}

	return false;
}

void System::readFromFile()
{
	std::ifstream input(SN_FILE_NAME, std::ios::in | std::ios::binary);
	if (!input.is_open())
		return;

	size_t usersCount = 0;
	input.read((char*)&usersCount, sizeof(size_t));
	for (int i = 0; i < usersCount; i++)
	{
		User readTemp;
		readTemp.readFromBinaryFile(input);
		users.addT(readTemp);
	}


	size_t topicsCount = 0;
	input.read((char*)&topicsCount, sizeof(size_t));
	for (int i = 0; i < topicsCount; i++)
	{
		Topic readTemp;
		readTemp.readFromBinaryFile(input);
		topics.addT(readTemp);
	}

	input.clear();
	input.close();
}

void System::writeToFile() const {
	std::ofstream output(SN_FILE_NAME, std::ios::out | std::ios::binary);
	if (!output.is_open())
		return;

	size_t usersCount = users.getTCount();
	output.write((const char*)&usersCount, sizeof(usersCount));
	for (int i = 0; i < usersCount; i++)
	{
		users[i].writeToBinaryFile(output);
	}


	size_t topicsCount = topics.getTCount();
	output.write((const char*)&topicsCount, sizeof(size_t));
	for (int i = 0; i < topicsCount; i++)
	{
		topics[i].writeToBinaryFile(output);
	}

	output.clear();
	output.close();
}

void System::exit()const {
	writeToFile();
	std::exit(0);
}
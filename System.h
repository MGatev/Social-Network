#pragma once
#include "User.h"
#include "Question.h"
#include "Topic.h"
#include "Comment.h"
#include "Collection.hpp"
#include <iostream>
#include <fstream>

class System {
	Collection<User> users;
	Collection<Topic> topics;

	mutable int openedTopic = -1;
	mutable int userLoggedIn = -1;
	mutable int openedQuestion = -1;

public:
	void printInstructions()const;

	bool signUp(const MyString& firstName, const MyString& lastName, const MyString& password);
	bool login(const MyString& firstName, const MyString& password)const;

	bool search(const MyString& keyWord)const;
	bool createTopic(const MyString& title, const MyString& description);
	bool open(const MyString& fullName);
	bool open(const size_t idNumber);
	bool p_open(const size_t questionId);
	bool p_open(const MyString& title);
	bool list()const;
	bool comments()const;

	bool post(const Question& questionToPost);
	bool comment(const MyString& newComment);
	bool reply(const size_t id, const MyString& creator, const MyString& newReply);
	bool upVote(const size_t id);
	bool downVote(const size_t id);

	bool whoAmI()const;
	bool about(const size_t id)const;

	bool logout();
	bool p_close();
	bool quit();
	
	void readFromFile();
	void writeToFile() const;
	
	void exit()const;
};
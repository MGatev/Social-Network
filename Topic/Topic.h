#pragma once
#include "MyString.h"
#include "User.h"
#include "Question.h"
#include "Collection.hpp"
#include <fstream>


class Topic{
	MyString title;
	MyString creatorName;
	MyString description;
	size_t id;

	Collection<Question> questions;

	mutable bool isOpen = false;

	static size_t idCount;

public:
	Topic();
	Topic(const MyString& title, const MyString& description, const MyString& creator);

	const MyString& getTitle()const;
	const MyString& getDescription()const;
	const size_t getId()const;
	const MyString& getCreator()const;
	const bool getIsOpen()const;
	const Collection<Question>& getQuestions()const; //constant access
	Collection<Question>& getQuestions(); //non-constant access


	void setTitle(const MyString& title);
	void setDescription(const MyString& description);

	void changeIsOpen();
	void addQuestion(const Question& questionToPost);
	void addQuestion(Question&& questionToPost);//move

	void printTopic()const;

	void readFromBinaryFile(std::ifstream& input);
	void writeToBinaryFile(std::ofstream& output) const;

	static void readIdCountFromBinary(std::ifstream& input);
	static void writeIdCountToBinary(std::ofstream& output);
};

#pragma once
#include "MyString.h"
#include "Collection.hpp"
#include "Comment.h"
#include <fstream>

class Question {
	MyString title;
	MyString description;
	size_t id;

	Collection<Comment> comments;

	mutable bool isOpen = false;
	static size_t idCount;

public:
	Question();
	Question(const MyString& title, const MyString& desc);
	const MyString& getTitle()const;
	size_t getId()const;
	bool getIsOpen()const;

	void printQuestion()const;
	const Collection<Comment>& getComments()const;
	Collection<Comment>& getComments();

	void changeIsOpen();
	void addComment(const Comment& commentToPost);
	void addComment(Comment&& commentToPost); //move

	void readFromBinaryFile(std::ifstream& input);
	void writeToBinaryFile(std::ofstream& output) const;

	static void readIdCountFromBinary(std::ifstream& input);
	static void writeIdCountToBinary(std::ofstream& output);
};
#pragma once
#include "MyString.h"
#include "User.h"
#include "Collection.hpp"
#include "UpDownVotes.h"
#include <fstream>


class Comment {
protected:
	MyString creator;
	MyString content;
	size_t id;
	
	UpDownVotes votes;
	Collection<Comment> replies;

	static size_t idCount;

public:
	Comment();

	Comment(const MyString& creator, const MyString& content);
	void printComment()const;

	const Collection<Comment>& getReplies()const;
	Collection<Comment>& getReplies();

	size_t getID()const;

	bool addUpVote(const size_t userID);
	bool addDownVote(const size_t userID);
	bool removeUpVote(const size_t userID);
	bool removeDownVote(const size_t userID);

	bool isAlreadyUpVoted(const size_t userID)const;
	bool isAlreadyDownVoted(const size_t userID)const;

	void readFromBinaryFile(std::ifstream& input);
	void writeToBinaryFile(std::ofstream& output) const;

	static void readIdCountFromBinary(std::ifstream& input);
	static void writeIdCountToBinary(std::ofstream& output);
};

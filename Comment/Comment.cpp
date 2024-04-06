#include "Comment.h"
#include "HelpFunctions.h"

size_t Comment::idCount = 1;

Comment::Comment() : id(0), creator(), content(), replies(), votes(){}

Comment::Comment(const MyString& creator, const MyString& content) {
	id = idCount++;
	this->creator = creator;
	this->content = content;
}

void Comment::printComment()const {
	std::cout << "	>>" << content << " {id:" << id << "}"
		<< "  Likes: " << votes.getUpVotesCount()
		<< "  Dislikes: " << votes.getDownVotesCount()
		<< "  Created by: " << creator << std::endl;

	for (size_t i = 0; i < replies.getTCount(); i++)
	{	
		std::cout << "	";
		replies[i].printComment();
	}
	
}

size_t Comment::getID()const {
	return id;
}

const Collection<Comment>& Comment::getReplies()const {
	return replies;
}

Collection<Comment>& Comment::getReplies() {
	return replies;
}

bool Comment::addUpVote(const size_t userID) {
	votes.addUpVote(userID);
	return true;
}
bool Comment::addDownVote(const size_t userID) {
	votes.addDownVote(userID);
	return true;
}
bool Comment::removeUpVote(const size_t indx) {
	votes.removeUpVote(indx);
	return true;
}
bool Comment::removeDownVote(const size_t userID) {
	votes.removeDownVote(userID);
	return true;
}

bool Comment::isAlreadyUpVoted(const size_t userID)const {
	for (size_t i = 0; i < votes.getUpVotesCount(); i++)
	{
		if (votes.getUpVotes()[i] == userID)
			return true;
	}
	return false;
}
bool Comment::isAlreadyDownVoted(const size_t userID)const {
	for (size_t i = 0; i < votes.getDownVotesCount(); i++)
	{
		if (votes.getDownVotes()[i] == userID)
			return true;
	}
	return false;
}

void Comment::readFromBinaryFile(std::ifstream& input) {
	readIdCountFromBinary(input);

	creator = readStringFromBinaryFile(input);
	content = readStringFromBinaryFile(input);
	input.read((char*)&id, sizeof(id));
	votes.readFromBinaryFile(input);

	size_t repliesCount = 0;
	input.read((char*)&repliesCount, sizeof(repliesCount));
	for (size_t i = 0; i < repliesCount; i++)
	{
		Comment readTemp;
		readTemp.readFromBinaryFile(input);
		replies.addT(readTemp);
	}
}

void Comment::writeToBinaryFile(std::ofstream& output) const {
	writeIdCountToBinary(output);

	writeStringToBinaryFile(output, creator);
	
	writeStringToBinaryFile(output, content);
	output.write((const char*)&id, sizeof(id));
	votes.writeToBinaryFile(output);

	size_t repliesCount = replies.getTCount();

	output.write((const char*)&repliesCount, sizeof(repliesCount));
	for (size_t i = 0; i < repliesCount; i++)
		replies[i].writeToBinaryFile(output);
}

void Comment::writeIdCountToBinary(std::ofstream& output) {
	output.write((const char*)&idCount, sizeof(idCount));
}

void Comment::readIdCountFromBinary(std::ifstream& input) {
	size_t temp = 0;
	input.read((char*)&temp, sizeof(temp));
	idCount = temp;
}

#include "Question.h"
#include "HelpFunctions.h"

size_t Question::idCount = 1;

Question::Question() : title(), description(), id(0){}

Question::Question(const MyString& title, const MyString& desc) :
				   title(title), description(desc){
	id = idCount++;
}

void Question::printQuestion()const {
	std::cout << "	>>" << title << " {id:" << id << "}" << std::endl
		<< "	Description: " << description << std::endl <<std::endl;
}

const Collection<Comment>& Question::getComments()const {
	return comments;
}

Collection<Comment>& Question::getComments(){
	return comments;
}

const MyString& Question::getTitle()const {
	return title;
}

size_t Question::getId()const {
	return id;
}

bool Question::getIsOpen()const {
	return isOpen;
}

void Question::changeIsOpen() {
	isOpen = !isOpen;
}

void Question::addComment(const Comment& commentToPost) {
	comments.addT(commentToPost);
}

void Question::addComment(Comment&& commentToPost) {
	comments.addT(std::move(commentToPost));
}

void Question::readFromBinaryFile(std::ifstream& input) {
	readIdCountFromBinary(input);

	title = readStringFromBinaryFile(input);
	description = readStringFromBinaryFile(input);
	input.read((char*)&id, sizeof(size_t));

	size_t commentsCount = 0;
	input.read((char*)&commentsCount, sizeof(commentsCount));

	for (size_t i = 0; i < commentsCount; i++)
	{
		Comment readTemp;
		readTemp.readFromBinaryFile(input);
		comments.addT(readTemp);
	}

}

void Question::writeToBinaryFile(std::ofstream& output) const {
	writeIdCountToBinary(output);

	writeStringToBinaryFile(output,title);
	writeStringToBinaryFile(output, title);
	output.write((const char*)&id, sizeof(size_t));

	size_t commentsCount = comments.getTCount();
	output.write((const char*)&commentsCount, sizeof(commentsCount));

	for (size_t i = 0; i < commentsCount; i++)
		comments[i].writeToBinaryFile(output);
}

void Question::writeIdCountToBinary(std::ofstream& output) {
	output.write((const char*)&idCount, sizeof(idCount));
}

void Question::readIdCountFromBinary(std::ifstream& input) {
	size_t temp = 0;
	input.read((char*)&temp, sizeof(temp));
	idCount = temp;
}
#include "Topic.h"
#include "HelpFunctions.h"

size_t Topic::idCount = 1;

Topic::Topic() :title(),creatorName(),description(), questions(), id(0){}

Topic::Topic(const MyString& _title, const MyString& _description, const MyString& _creator) : questions(){
	title = _title;
	description = _description;
	creatorName = _creator;
	id = idCount++;
}

const MyString& Topic::getTitle() const {
	return title;
}

const MyString& Topic::getDescription()const {
	return description;
}

const size_t Topic::getId()const {
	return id;
}

const MyString& Topic::getCreator()const {
	return creatorName;
}

const bool Topic::getIsOpen()const {
	return isOpen;
}

const Collection<Question>& Topic::getQuestions()const {
	return questions;
}

Collection<Question>& Topic::getQuestions() {
	return questions;
}

void Topic::setTitle(const MyString& title) {
	this->title = title;
}

void Topic::setDescription(const MyString& description) {
	this->description = description;
}

void Topic::changeIsOpen() {
	isOpen = !isOpen;
}

void Topic::addQuestion(const Question& questionToPost){
	questions.addT(questionToPost);
}

void Topic::addQuestion(Question&& questionToPost) {
	questions.addT(std::move(questionToPost));
}

void Topic::printTopic()const {
	std::cout << title << " {id:" << id << "}" << std::endl
		<< "Description: " << description << std::endl
		<< "Created By: " << creatorName << std::endl << std::endl;
}

void Topic::readFromBinaryFile(std::ifstream& input) {
	readIdCountFromBinary(input);

	title = readStringFromBinaryFile(input);
	creatorName = readStringFromBinaryFile(input);
	description = readStringFromBinaryFile(input);
	input.read((char*)&id, sizeof(size_t));

	size_t questionCount = 0;
	input.read((char*)&questionCount, sizeof(size_t));

	for (int i = 0; i < questionCount; i++)
	{
		Question readTemp;
		readTemp.readFromBinaryFile(input);
		questions.addT(readTemp);
	}
}

void Topic::writeToBinaryFile(std::ofstream& output) const {
	writeIdCountToBinary(output);

	writeStringToBinaryFile(output, title);
	writeStringToBinaryFile(output, creatorName);
	writeStringToBinaryFile(output, description);
	output.write((const char*)&id, sizeof(id));

	size_t questionCount = questions.getTCount();
	output.write((const char*)&questionCount, sizeof(questionCount));

	for (int i = 0; i < questionCount; i++)
	{
		questions[i].writeToBinaryFile(output);
	}
}

void Topic::writeIdCountToBinary(std::ofstream& output) {
	output.write((const char*)&idCount, sizeof(idCount));
}

void Topic::readIdCountFromBinary(std::ifstream& input) {
	size_t temp = 0;
	input.read((char*)&temp, sizeof(temp));
	idCount = temp;
}
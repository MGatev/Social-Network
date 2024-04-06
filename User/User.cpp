#include "User.h"
#include "HelpFunctions.h"

size_t User::idCount = 1;

User::User() : firstName(), lastName(), password(), points(0), id(0) {}

User::User(const MyString& _firstName, const MyString& _lastName, const MyString& _password) {
	firstName = _firstName;
	lastName = _lastName;
	password = _password;

	id = idCount++;
	points = 0;
}

const MyString& User::getFirstName()const {
	return firstName;
}

const MyString& User::getLastName()const {
	return lastName;
}

const MyString& User::getPassword()const {
	return password;
}

bool User::getIsLoggedIn()const {
	return isLoggedIn;
}

size_t User::getID()const {
	return id;
}

int User::getPoints()const {
	return points;
}

void User::setFirstName(const MyString& firstName) {
	this->firstName = firstName;
}

void User::setLastName(const MyString& lastName) {
	this->lastName = lastName;
}

void User::setPassword(const MyString& password) {
	this->password = password;
}

void User::setId(const size_t id) {
	this->id = id;
}

void User::setPoints(const int points) {
	this->points = points;
}

void User::changeIsLoggedIn() {
	isLoggedIn = !isLoggedIn;
}

void User::printUser()const {
	std::cout << "First name: " << firstName << std::endl << "Last name: " << lastName
		<< std::endl << "Points: " << points << std::endl;
}

void User::readFromBinaryFile(std::ifstream& input) {
	readIdCountFromBinary(input);

	firstName = readStringFromBinaryFile(input);
	lastName = readStringFromBinaryFile(input);
	password = readStringFromBinaryFile(input);

	input.read((char*)&id, sizeof(size_t));
	input.read((char*)&points, sizeof(int));
}

void User::writeToBinaryFile(std::ofstream& output) const {
	writeIdCountToBinary(output);

	writeStringToBinaryFile(output, firstName);
	writeStringToBinaryFile(output, lastName);
	writeStringToBinaryFile(output, password);

	output.write((const char*)&id, sizeof(size_t));
	output.write((const char*)&points, sizeof(int));
}

void User::writeIdCountToBinary(std::ofstream& output) {
	output.write((const char*)&idCount, sizeof(idCount));
}

void User::readIdCountFromBinary(std::ifstream& input) {
	size_t temp = 0;
	input.read((char*)&temp, sizeof(temp));
	idCount = temp;
}

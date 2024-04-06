#pragma once
#include "MyString.h"
#include <fstream>

class User {
	MyString firstName;
	MyString lastName;
	MyString password;
	size_t id;
	int points;

	bool isLoggedIn = false;

	static size_t idCount;

public:

	User();
	User(const MyString& firstName, const MyString& lastName, const MyString& password);

	const MyString& getFirstName()const;
	const MyString& getLastName()const;
	const MyString& getPassword()const;
	bool getIsLoggedIn()const;
	size_t getID()const;
	int getPoints()const;

	void setFirstName(const MyString& firstName);
	void setLastName(const MyString& lastName);
	void setPassword(const MyString& password);
	void setId(const size_t id);
	void setPoints(const int points);

	void changeIsLoggedIn();
	void printUser()const;
	void readFromBinaryFile(std::ifstream& input);
	void writeToBinaryFile(std::ofstream& output) const;

	static void readIdCountFromBinary(std::ifstream& input);
	static void writeIdCountToBinary(std::ofstream& output);
};

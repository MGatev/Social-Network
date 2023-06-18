#include "OpenCommand.h"
#include <sstream>
const int ASCII_ZERO = 48;
const int ASCII_NINE = 57;

namespace {

	int parseStringToInt(const MyString& str) {
		std::stringstream temp;
		temp << str.c_str();
		int num = 0;
		temp >> num;
		return num;
	}

	int convertToId(const MyString& keyword) {
		for (size_t i = 0; i < keyword.length(); i++)
		{
			char temp = keyword.c_str()[i];
			if (temp < ASCII_ZERO || temp > ASCII_NINE)
				return -1;
		}

		return parseStringToInt(keyword);
	}
}

OpenCommand::OpenCommand(const MyString& keyWord) : fullName(keyWord) {}

void OpenCommand::execute(System& mySystem) {
	if (convertToId(fullName) < 0)
		mySystem.open(fullName);
	else
		mySystem.open(convertToId(fullName));

}
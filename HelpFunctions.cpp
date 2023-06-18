#include "HelpFunctions.h"
#include <fstream>

void writeStringToBinaryFile(std::ofstream& output, const MyString& str)
{
	size_t len = str.length();
	output.write((const char*)&len, sizeof(len));

	output.write(str.c_str(), sizeof(char) * len);
}

MyString readStringFromBinaryFile(std::ifstream& input)
{
	size_t strLength = 0;
	input.read((char*)&strLength, sizeof(strLength));

	char* buff = new char[strLength + 1];
	input.read(buff, sizeof(char) * strLength);

	buff[strLength] = '\0';

	MyString toReturn(buff);

	delete[] buff;

	return toReturn;
}
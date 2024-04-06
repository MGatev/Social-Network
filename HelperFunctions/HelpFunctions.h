#pragma once
#include "MyString.h"

void writeStringToBinaryFile(std::ofstream& output, const MyString& str);

MyString readStringFromBinaryFile(std::ifstream& ifs);

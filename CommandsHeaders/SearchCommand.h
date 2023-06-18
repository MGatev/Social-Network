#pragma once
#include "Command.h"

class SearchCommand : public Command
{
	MyString keyWord;

public:
	SearchCommand(const MyString& keyWord);
	SearchCommand(const SearchCommand&) = delete;
	SearchCommand& operator=(const SearchCommand&) = delete;
	void execute(System& mySystem) override;
};
#include "SearchCommand.h"

SearchCommand::SearchCommand(const MyString& keyWord) : keyWord(keyWord){}

void SearchCommand::execute(System& mySystem) {
	mySystem.search(keyWord);
}
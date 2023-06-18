#include "ReplyCommand.h"

ReplyCommand::ReplyCommand(const MyString& creator, const MyString& newReply, const size_t id) :
	creator(creator), newReply(newReply), id(id)
{}

void ReplyCommand::execute(System& mySystem) {
	mySystem.reply(id, creator, newReply);
}
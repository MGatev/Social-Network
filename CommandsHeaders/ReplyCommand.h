#pragma once
#include "Command.h"

class ReplyCommand : public Command
{
	MyString creator;
	MyString newReply;
	size_t id;
public:
	ReplyCommand(const MyString& creator, const MyString& newComment, const size_t id);
	ReplyCommand(const ReplyCommand&) = delete;
	ReplyCommand& operator=(const ReplyCommand&) = delete;
	void execute(System& mySystem) override;
};
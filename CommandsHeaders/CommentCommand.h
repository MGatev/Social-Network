#pragma once
#include "Command.h"

class CommentCommand : public Command
{
	MyString newComment;
public:
	CommentCommand(const MyString& newComment);
	CommentCommand(const CommentCommand&) = delete;
	CommentCommand& operator=(const CommentCommand&) = delete;
	void execute(System& mySystem) override;
};
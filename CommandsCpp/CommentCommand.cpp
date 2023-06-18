#include "CommentCommand.h"

CommentCommand::CommentCommand(const MyString& newComment) : newComment(newComment)
{}

void CommentCommand::execute(System& mySystem) {
	mySystem.comment(newComment);
}
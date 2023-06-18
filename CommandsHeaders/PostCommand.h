#pragma once
#include "Command.h"

class PostCommand : public Command
{
	Question questionToPost;

public:
	PostCommand(const Question& questionToAdd);
	PostCommand(Question&& questionToAdd);
	PostCommand(const PostCommand&) = delete;
	PostCommand& operator=(const PostCommand&) = delete;
	void execute(System& mySystem) override;
};
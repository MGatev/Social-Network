#include "PostCommand.h"

PostCommand::PostCommand(const Question& questionToAdd) : questionToPost(questionToAdd)
{}
PostCommand::PostCommand(Question&& questionToAdd) : questionToPost(std::move(questionToAdd))
{}

void PostCommand::execute(System& mySystem)
{
	mySystem.post(questionToPost);
}
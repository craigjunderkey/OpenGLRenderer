#include "UniformCommandBlock.h"
#include <string>

using namespace Graphics;

UniformCommandBlock::UniformCommandBlock()
{
}

UniformCommandBlock::~UniformCommandBlock()
{
	for (UniformCommand* command : this->commands_)
	{
		delete command;
	}
}

void UniformCommandBlock::addCommand(UniformCommand* command)
{
	this->commands_.push_back(command);
}

void UniformCommandBlock::execute(UniformManager& uniformManager)
{
	for (auto& command : this->commands_)
	{
		command->execute(uniformManager);
	}
}
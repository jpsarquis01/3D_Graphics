#pragma once

#include "Command.h"

class CmdModel : public Command
{
public:
	const char* GetName() override
	{
		return "LoadModel";
	}
	const char* GetDescription() override
	{
		return
			"LoadModel(fileName)\n"
			"\n"
			"- loads a model from file and makes it available for drawing";
	}
	bool Execute(const std::vector<std::string>& params) override;
};
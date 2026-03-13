#pragma once
#include "Command.h"

class CmdSetCorrectUV : public Command
{
public:
	const char* GetName() override
	{
		return "SetCorrectUV";
	}
	const char* GetDescription() override
	{
		return
			"SetCorrectUV(bool correctUV)\n"
			"\n"
			"- sets whether to correct UV coordinates for perspective distortion"
			"\n"
			"- enables/disables correct uv for texture objs";
	}
	bool Execute(const std::vector<std::string>& params) override;
};
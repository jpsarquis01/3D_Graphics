#pragma once
#include "Command.h"

class CmdBeginDraw : public Command
{
public:
	const char* GetName() override
	{
		return "Begin Draw";
	}
	const char* GetDescription() override
	{
		return "Begin Draw(topology)\n"
			"\n"
			"- start storing vertices\n"
			"- store topology (point, line, triagle";

	}
}
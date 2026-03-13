#pragma once
#include "Command.h"

class CmdSetAddressMode : public Command
{
public:
	const char* GetName() override
	{
		return "SetAddressMode";
	}
	const char* GetDescription() override
	{
		return
			"SetAddressMode(AddressMode addressMode)\n"
			"\n"
			"- sets the address mode for texture sampling\n"
			"- AddressMode can be Border, Clamp, Wrap, Mirror";
	}
	bool Execute(const std::vector<std::string>& params) override;
};
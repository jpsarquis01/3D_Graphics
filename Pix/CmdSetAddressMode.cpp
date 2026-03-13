#include "CmdSetAddressMode.h"
#include "TextureManager.h"

bool CmdSetAddressMode::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	AddressMode addressMode = AddressMode::Border;
	if (params[0] == "Border")
	{
		addressMode = AddressMode::Border;
	}
	else if (params[0] == "Clamp")
	{
		addressMode = AddressMode::Clamp;
	}
	else if (params[0] == "Wrap")
	{
		addressMode = AddressMode::Wrap;
	}
	else if (params[0] == "Mirror")
	{
		addressMode = AddressMode::Mirror;
	}
	else
	{
		return false;
	}

	TextureManager::Get()->SetAdressMode(addressMode);
	return true;

}
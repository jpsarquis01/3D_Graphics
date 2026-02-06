#include "CmdEndDraw.h"
#include "PrimitivesManager.h"

bool CmdEndDraw::Execute(const std::vector<std::string>& params)
{
	// Sends vertices to rasterizer
	return PrimitivesManager::Get()->EndDraw();
}
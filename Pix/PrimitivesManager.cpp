#include "PrimitivesManager.h"
#include "Rasterizer.h"


PrimitiveManager* PrimitiveManager::Get()
{
	static PrimitiveManager sInstance;
	return &sInstance;
}

PrimitiveManager::PrimitiveManager()
{

}

bool PrimitiveManager::BeginDraw(Topology topology)
{
	mVertexBuffer.clear();
	mTopology = topology;
	mDrawBegin = true;
	return true;
}

void PrimitiveManager::AddVertex(const Vertex& vertex)
{
	if (mDrawBegin)
	{
		mVertexBuffer.push_back(vertex);
	}
}

bool PrimitiveManager::EndDraw()
{
	if (!mDrawBegin)
	{
		return false;
	}

	Rasterizer* rasterizer = Rasterizer::Get();

	switch (mTopology)
	{
	case Topology::Point:
	{
		for (uint32_t i = 0; i < mVertexBuffer.size(); ++i)
		{
			rasterizer->DrawPoint(mVertexBuffer[i]);
		}
	}
	break;
	case Topology::Line:
	{
		for (uint32_t i = 0; i < mVertexBuffer.size(); i += 2)
		{
			rasterizer->DrawLine(mVertexBuffer[i - 1], mVertexBuffer[i]);
		}
	}
	break;
	case Topology::Triangle:
	{
		for (uint32_t i = 0; i < mVertexBuffer.size(); i += 3)
		{
			rasterizer->DrawTriangle(mVertexBuffer[i - 2], mVertexBuffer[i - 1], mVertexBuffer[i]);
		}
	}
	break;
	default:
	break;
	}
}


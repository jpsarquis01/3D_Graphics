#pragma once
#include "Vertex.h"

enum class Topology
{
	Point,
	Line,
	Triangle
};

class PrimitiveManager
{
public:
	static PrimitiveManager* Get();

	// Start accepting vertices
	bool BeginDraw(Topology topology);
	//Add vertices to the list, only if drawing is enabled
	void AddVertex(const Vertex& vertex);
	// Send all the stored vertices to the reastirizer as especified topoloogy
	bool EndDraw();

private:
	PrimitiveManager();

	std::vector<Vertex> mVertexBuffer;
	Topology mTopology = Topology::Point;
	bool mDrawBegin = false;
};
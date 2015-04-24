#pragma once

class GraphNode
{
public:
	bool visited;
	int boardState[4][4];
	GraphNode *contiguousNodes[4];

	GraphNode(int **board);
};
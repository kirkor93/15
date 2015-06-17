#pragma once

#include "Algorithm.h"

class BFS :
	public Algorithm
{
public:
	BFS();
	virtual void Solve(GraphNode *startNode, int maxIterations);
};
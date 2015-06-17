#pragma once

#include "Algorithm.h"

class DFS : 
	public Algorithm
{
public:
	DFS();
	virtual void Solve(GraphNode *startNode, int maxIterations);
};


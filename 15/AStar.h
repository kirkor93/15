#pragma once

#include "Algorithm.h"

class AStar :
	public Algorithm
{
public:
	AStar();
	virtual void Solve(GraphNode *startNode, int maxIterations);
};
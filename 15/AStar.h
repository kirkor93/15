#pragma once

#include "Algorithm.h"

class AStar :
	public Algorithm
{
public:
	AStar(GraphNode *startNode, int maxIterations);
};
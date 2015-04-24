#include "GraphNode.h"

GraphNode::GraphNode(int **board)
{
	this->visited = false;
	for (int i = 0; i < 4; i += 1)
	{
		this->contiguousNodes[i] = nullptr;
	}
	for (int i = 0; i < 4; i += 1)
	{
		for (int j = 0; j < 4; j += 1)
		{
			this->boardState[i][j] = board[i][j];
		}
	}
}
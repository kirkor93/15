#include "DFS.h"


DFS::DFS() : Algorithm()
{
	name = "DFS";
}

void DFS::Solve(GraphNode *startNode, int maxIterations)
{
	StartTimer();
	stack<GraphNode*> nodesStack;

	GraphNode *node = new GraphNode(startNode);
	elements.push_back(node);
	nodesStack.push(node);
	node->visited = true;
	int iterations = 0;
	while (!node->IsSolution())
	{
		node->visited = true;
		node->FindNeighbours(elements);
		node->PushNeighbours(nodesStack);
		node = nodesStack.top();
		while ((node = nodesStack.top())->visited)
		{
			nodesStack.pop();
		}
		iterations++;
		if (iterations > maxIterations)
		{
			ShowResult(false, iterations);
			StopTimer();
			return;
		}
	}
	StopTimer();
	ShowResult(true, iterations, node);
}
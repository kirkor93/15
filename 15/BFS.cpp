#include "BFS.h"


BFS::BFS(GraphNode *startNode, int maxIterations)
{
	name = "BFS";

	queue<GraphNode*> nodesQueue;

	GraphNode *node = new GraphNode(startNode);
	elements.push_back(node);
	nodesQueue.push(node);
	node->visited = true;
	int iterations = 0;
	while (!node->IsSolution())
	{
		node->visited = true;
		node->FindNeighbours(elements);
		node->PushNeighbours(nodesQueue);
		nodesQueue.pop();
		while ((node = nodesQueue.front())->visited)
		{
			nodesQueue.pop();
		}

		iterations++;
		if (iterations > maxIterations)
		{
			ShowResult(false, iterations);
			return;
		}
	}
	ShowResult(true, iterations, node);
}

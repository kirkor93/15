#include "AStar.h"


AStar::AStar(GraphNode *startNode, int maxIterations)
{
	name = "A*";

	priority_queue<GraphNode*, vector<GraphNode*>, MyComparator> nodesQueue;

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
		node = nodesQueue.top();
		while ((node = nodesQueue.top())->visited)
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


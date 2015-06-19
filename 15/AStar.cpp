#include "AStar.h"


AStar::AStar() : Algorithm()
{
	name = "A*";
}

void AStar::Solve(GraphNode *startNode, int maxIterations)
{
	StartTimer();
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
			StopTimer();
			return;
		}
	}
	StopTimer();
	ShowResult(true, iterations, node);
}
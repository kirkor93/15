#pragma once

#include <list>
#include <stack>
#include <random>
#include <chrono>
#include <queue>

using namespace std;

class GraphNode
{
public:
	bool visited;
	int **boardState;
	GraphNode *contiguousNodes[4];

	GraphNode(int **board);
	~GraphNode();

	bool IsSolution();
	void FindNeighbours(list<GraphNode*> &list);
	bool CompareTo(int** other);
	void PushNeighbours(stack<GraphNode*>& membersList);
	void PushNeighbours(queue<GraphNode*>& membersStack);

private:
	void CloneBoard(int **original, int **cloned);
	void AddNeighbour(int **boardState, list<GraphNode*>& list);
};
#pragma once

#include <list>
#include <stack>
#include <random>
#include <chrono>
#include <queue>

using namespace std;

struct MyComparator;

class GraphNode
{
public:
	bool visited;
	int **boardState;
	int h;
	GraphNode *contiguousNodes[4];

	GraphNode(int **board);
	~GraphNode();

	bool IsSolution();
	void FindNeighbours(list<GraphNode*> &list);
	bool CompareTo(int** other);
	void PushNeighbours(stack<GraphNode*>& membersList);
	void PushNeighbours(queue<GraphNode*>& membersStack);
	void PushNeighbours(priority_queue<GraphNode*, vector<GraphNode*>, MyComparator> &membersQueue);
	int CountHeuristic() const;
	//bool operator<(const GraphNode& rhs);

private:
	void CloneBoard(int **original, int **cloned);
	void AddNeighbour(int **boardState, list<GraphNode*>& list);
};

struct MyComparator 
{
	bool operator() (const GraphNode* arg1, const GraphNode* arg2) const 
	{
		return arg1->h > arg2->h;
	}
};
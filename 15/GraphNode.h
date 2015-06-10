#pragma once

#include <iostream>
#include <list>
#include <stack>
#include <random>
#include <chrono>
#include <queue>

using namespace std;

struct MyComparator;

class GraphNode
{
	friend MyComparator;
public:
	bool visited;

private:
	int **boardState;
	int h;
	GraphNode *contiguousNodes[4];

public:
	GraphNode();
	GraphNode(int **board);
	GraphNode(GraphNode *original);
	~GraphNode();

	void Shuffle(int steps);
	void Display();
	bool IsSolution();
	void FindNeighbours(list<GraphNode*> &list);
	bool CompareTo(int** other);
	void PushNeighbours(stack<GraphNode*>& membersList);
	void PushNeighbours(queue<GraphNode*>& membersStack);
	void PushNeighbours(priority_queue<GraphNode*, vector<GraphNode*>, MyComparator> &membersQueue);
	int CountHeuristic() const;

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
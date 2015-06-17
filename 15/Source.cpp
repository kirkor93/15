#include "GraphNode.h"
#include "AStar.h"
#include "BFS.h"
#include "DFS.h"

using namespace std;

int main()
{
	GraphNode *startNode = new GraphNode();
	startNode->ShuffleManually();

	cout << "Max iterations: ";
	int iterations;
	cin >> iterations;

	cout << "Before solving: \n";
	startNode->Display();

	AStar aStar;
	aStar.Solve(startNode, iterations);
	BFS bfs;
	bfs.Solve(startNode, iterations);
	DFS dfs;
	dfs.Solve(startNode, iterations);

	delete startNode;
	_getch();
	return 0;
}
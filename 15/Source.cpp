#include "GraphNode.h"
#include "AStar.h"
#include "BFS.h"
#include "DFS.h"

using namespace std;

int main()
{
	cout << "How many times do you want to shuffle the board: ";
	int counter;
	cin >> counter;
	cout << "Max iterations: ";
	int iterations;
	cin >> iterations;

	GraphNode *startNode = new GraphNode();
	startNode->Shuffle(counter);
	cout << "Before solving: \n";
	startNode->Display();

	AStar(startNode, iterations);
	BFS(startNode, iterations);
	DFS(startNode, iterations);

	delete startNode;
	cin >> counter;
	return 0;
}
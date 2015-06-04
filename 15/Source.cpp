#include <iostream>
#include <list>
#include "GraphNode.h"
#include "MoveDirection.h"
#include <stack>


using namespace std;

int** InitializeBoard()
{
	int** board = new int *[4];
	for (int i = 0; i < 4; i += 1)
	{
		board[i] = new int[4];
	}

	for (int i = 0; i < 4; i += 1)
	{
		for (int j = 1; j < 5; j += 1)
		{
			board[i][j - 1] = i * 4 + j;
		}
	}
	board[3][3] = 0;

	return board;
}

void ShuffleBoard(int **board, int steps)
{
	int posX = 0, posY = 0;

	for (int i = 0; i < 4; i += 1)
	{
		for (int j = 0; j < 4; j += 1)
		{
			if (board[i][j] == 0)
			{
				posX = i;
				posY = j;
			}
		}
	}
	unsigned seed = (unsigned int)chrono::system_clock::now().time_since_epoch().count();
	minstd_rand0 generator(seed);
	int lastCase = -1;
	for (int i = 0; i < steps; i += 1)
	{
		int newPosX = 0;
		int newPosY = 0;
		do
		{
			newPosX = posX;
			newPosY = posY;

			int direction = generator() % 4;
			if (direction == lastCase)
			{
				continue;
			}
			switch (direction)
			{
			case 0:
				lastCase = 2;
				newPosX += 1;
				break;
			case 1:
				lastCase = 3;
				newPosY += 1;
				break;
			case 2:
				lastCase = 0;
				newPosX -= 1;
				break;
			case 3:
				lastCase = 1;
				newPosY -= 1;
				break;
			}
			
		} while (newPosX < 0 || newPosY < 0 || newPosX > 3 || newPosY > 3);

		int tmp = board[posX][posY];
		board[posX][posY] = board[newPosX][newPosY];
		board[newPosX][newPosY] = tmp;

		posX = newPosX;
		posY = newPosY;
	}
}

void ReleaseBoard(int **board)
{
	for (int i = 0; i < 3; i += 1)
	{
		delete[] board[i];
	}
	delete[] board;
}

void DisplayBoard(int **board)
{
	for (int i = 0; i < 4; i += 1)
	{
		for (int j = 0; j < 4; j += 1)
		{
			cout << board[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void DFS(int **board, int maxIterations)
{
	//stack<MoveDirection> moves;
	stack<GraphNode*> nodesStack;
	list<GraphNode*> list;

	GraphNode *node = new GraphNode(board);
	list.push_back(node);
	nodesStack.push(node);
	node->visited = true;
	int iterations = 0;
	while (!node->IsSolution())
	{
		node->visited = true;
		node->FindNeighbours(list);
		node->PushNeighbours(nodesStack);		
		node = nodesStack.top();
		while ((node = nodesStack.top())->visited)
		{
			nodesStack.pop();
		}
		iterations++;
		if (iterations > maxIterations)
		{
			cout << "DFS exceeded max iterations value :(\n";
			return;
		}
		//DisplayBoard(node->boardState);
	}

	cout << "DFS did it in: " << iterations << " iterations!!!!!! \n";
	DisplayBoard(node->boardState);

	delete node;
}

void BFS(int **board, int maxIterations)
{
	//stack<MoveDirection> moves;
	queue<GraphNode*> nodesStack;
	list<GraphNode*> list;

	GraphNode *node = new GraphNode(board);
	list.push_back(node);
	nodesStack.push(node);
	node->visited = true;
	int iterations = 0;
	while (!node->IsSolution())
	{
		node->visited = true;
		node->FindNeighbours(list);
		node->PushNeighbours(nodesStack);
		nodesStack.pop();
		while ((node = nodesStack.front())->visited)
		{
			nodesStack.pop();
		}
		
		iterations++;
		if (iterations > maxIterations)
		{
			cout << "BFS exceeded max iterations value :(\n";
			return;
		}
		//DisplayBoard(node->boardState);
	}

	cout << "BFS did it in: " << iterations << " iterations!!!!!! \n";
	DisplayBoard(node->boardState);

	delete node;
}

int main()
{
	cout << "How many times do you want to shuffle the board: ";
	int counter;
	cin >> counter;
	cout << "Max iterations: ";
	int iterations;
	cin >> iterations;

	int **board = InitializeBoard();
	ShuffleBoard(board, counter);
	cout << "Before solving: \n";
	DisplayBoard(board);

	BFS(board, iterations);
	DFS(board, iterations);
	ReleaseBoard(board);
	int a;
	cin >> a;
	return 0;
}
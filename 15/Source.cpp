#include <iostream>
#include <random>
#include <chrono>
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
	for (int i = 0; i < steps; i += 1)
	{
		int newPosX = 0;
		int newPosY = 0;
		do
		{
			newPosX = posX;
			newPosY = posY;

			int direction = generator() % 4;
			switch (direction)
			{
			case 0:
				newPosX += 1;
				break;
			case 1:
				newPosY += 1;
				break;
			case 2:
				newPosX -= 1;
				break;
			case 3:
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

void DFS(int **board)
{
	stack<MoveDirection> moves;
	list<GraphNode> graph;

	graph.push_back(GraphNode(board));
}

int main()
{
	int **board = InitializeBoard();
	DisplayBoard(board);
	ShuffleBoard(board, 500);
	DisplayBoard(board);

	DFS(board);

	ReleaseBoard(board);
	int a;
	cin >> a;
	return 0;
}
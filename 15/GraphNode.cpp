#include "GraphNode.h"

GraphNode::GraphNode()
{
	boardState = new int *[4];
	for (int i = 0; i < 4; i ++)
	{
		for (int j = 0; j < 4; j++)
		{
			boardState[i] = new int[4];
		}	
		contiguousNodes[i] = nullptr;
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			boardState[i][j] = i * 4 + j + 1;
		}
	}

	boardState[3][3] = 0;
	h = 0;
}

GraphNode::GraphNode(int **board)
{
	boardState = new int*[4];
	for (int i = 0; i < 4; i++)
	{
		boardState[i] = new int[4];
	}

	this->visited = false;
	for (int i = 0; i < 4; i += 1)
	{
		this->contiguousNodes[i] = nullptr;
	}
	for (int i = 0; i < 4; i += 1)
	{
		for (int j = 0; j < 4; j += 1)
		{
			this->boardState[i][j] = board[i][j];
		}
	}
	h = CountHeuristic();
}

GraphNode::GraphNode(GraphNode *original)
{
	boardState = new int*[4];
	for (int i = 0; i < 4; i++)
	{
		boardState[i] = new int[4];
	}
	for (int i = 0; i < 4; i += 1)
	{
		for (int j = 0; j < 4; j += 1)
		{
			boardState[i][j] = original->boardState[i][j];
		}
		if (original->contiguousNodes[i] != nullptr)
		{
			contiguousNodes[i] = new GraphNode(original->contiguousNodes[i]);
		}
	}
	h = original->h;
	visited = original->visited;
}

GraphNode::~GraphNode()
{	
	for (int i = 0; i < 4; i++)
	{
		delete[] boardState[i];
	}
	delete[] boardState;
}

void GraphNode::Shuffle(int steps)
{
	int posX = 0, posY = 0;

	for (int i = 0; i < 4; i += 1)
	{
		for (int j = 0; j < 4; j += 1)
		{
			if (boardState[i][j] == 0)
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
		int lastCase = -1;
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

		int tmp = boardState[posX][posY];
		boardState[posX][posY] = boardState[newPosX][newPosY];
		boardState[newPosX][newPosY] = tmp;

		posX = newPosX;
		posY = newPosY;
	}
	h = CountHeuristic();
}

void GraphNode::Display()
{
	for (int i = 0; i < 4; i += 1)
	{
		for (int j = 0; j < 4; j += 1)
		{
			cout << boardState[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

bool GraphNode::IsSolution()
{
	bool solution = true;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			int number = 4 * i + j;
			if (number == 16)
			{
				number = 0;
			}
			if (boardState[i][j - 1] != number)
			{
				solution = false;
			}
		}
	}
	return solution;
}

void GraphNode::FindNeighbours(list<GraphNode*>& membersList)
{
	int posX = 0, posY = 0;

	for (int i = 0; i < 4; i += 1)
	{
		for (int j = 0; j < 4; j += 1)
		{
			if (boardState[i][j] == 0)
			{
				posX = i;
				posY = j;
			}
		}
	}

	int **clonedBoard = new int*[4];
	for (int i = 0; i < 4; i++)
	{
		clonedBoard[i] = new int[4];
	}

	if (posX > 0)
	{
		CloneBoard(boardState, clonedBoard);
		int tmp = clonedBoard[posX][posY];
		clonedBoard[posX][posY] = clonedBoard[posX - 1][posY];
		clonedBoard[posX - 1][posY] = tmp;
		AddNeighbour(clonedBoard, membersList);
	}
	if (posY > 0)
	{
		CloneBoard(boardState, clonedBoard);
		int tmp = clonedBoard[posX][posY];
		clonedBoard[posX][posY] = clonedBoard[posX][posY - 1];
		clonedBoard[posX][posY - 1] = tmp;
		AddNeighbour(clonedBoard, membersList);
	}
	if (posX < 3)
	{
		CloneBoard(boardState, clonedBoard);
		int tmp = clonedBoard[posX][posY];
		clonedBoard[posX][posY] = clonedBoard[posX + 1][posY];
		clonedBoard[posX + 1][posY] = tmp;
		AddNeighbour(clonedBoard, membersList);
	}
	if (posY < 3)
	{
		CloneBoard(boardState, clonedBoard);
		int tmp = clonedBoard[posX][posY];
		clonedBoard[posX][posY] = clonedBoard[posX][posY + 1];
		clonedBoard[posX][posY + 1] = tmp;
		AddNeighbour(clonedBoard, membersList);
	}
	for (int i = 0; i < 4; i++)
	{
		delete[] clonedBoard[i];
	}
	delete[] clonedBoard;
}

void GraphNode::CloneBoard(int **original, int **cloned)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cloned[i][j] = original[i][j];
		}
	}
}

void GraphNode::AddNeighbour(int **boardState, list<GraphNode*>& membersList)
{
	unsigned seed = (unsigned int)chrono::system_clock::now().time_since_epoch().count();
	minstd_rand0 generator(seed);
	int index = -1;
	do
	{
		index = generator() % 4;
	} while (contiguousNodes[index] != nullptr);

	for (list<GraphNode*>::iterator it = membersList.begin(); it != membersList.end(); it++)
	{
		if ((*it)->CompareTo(boardState))
		{
			contiguousNodes[index] = *it;
			return;
		}
	}

	contiguousNodes[index] = new GraphNode(boardState);
	membersList.push_back(contiguousNodes[index]);
}

bool GraphNode::CompareTo(int** other)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (this->boardState[i][j] != other[i][j])
			{
				return false;
			}
		}
	}

	return true;
}

void GraphNode::PushNeighbours(stack<GraphNode*>& membersStack)
{
	for (int i = 0; i < 4; i++)
	{
		if (contiguousNodes[i] != nullptr && !contiguousNodes[i]->visited)
		{
			membersStack.push(contiguousNodes[i]);
		}
	}
}

void GraphNode::PushNeighbours(priority_queue<GraphNode*, vector<GraphNode*>, MyComparator> &membersQueue)
{
	for (int i = 0; i < 4; i++)
	{
		if (contiguousNodes[i] != nullptr && !contiguousNodes[i]->visited)
		{
			membersQueue.push(contiguousNodes[i]);
		}
	}
}

void GraphNode::PushNeighbours(queue<GraphNode*>& membersStack)
{
	for (int i = 0; i < 4; i++)
	{
		if (contiguousNodes[i] != nullptr && !contiguousNodes[i]->visited)
		{
			membersStack.push(contiguousNodes[i]);
		}
	}
}

int GraphNode::CountHeuristic() const
{
	int result = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int x = 0, y = 0;
			int pos = boardState[i][j];
			if (pos == 0)
			{
				pos = 16;
			}
			while ((x * 4 + y + 1) != pos)
			{
				y++;
				if (y > 3)
				{
					y = 0;
					x++;
				}
			}
			int tmp = abs(i - x);
			tmp += abs(j - y);
			result += tmp;
		}
	}
	return result;
}
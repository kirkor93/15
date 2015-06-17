#include "Algorithm.h"

Algorithm::Algorithm()
{
	elapsedTime = 0;
}

Algorithm::~Algorithm()
{
	for (list<GraphNode*>::iterator it = elements.begin(); it != elements.end(); it++)
	{
		delete *it;
		*it = nullptr;
	}
}

void Algorithm::ShowResult(bool succeded, int iterations, GraphNode *finalNode)
{
	if (succeded)
	{
		cout << name << " succeded after " << iterations << " iterations: \nand " << elapsedTime << " seconds\n";
		ShowMemory();
		if (finalNode != nullptr)
		{
			finalNode->Display();
		}
	}
	else
	{
		cout << name << " failed after " << iterations << " iterations. \n";
	}
}

void Algorithm::StartTimer()
{
	timer = clock();
}

void Algorithm::StopTimer()
{
	clock_t endTime = clock();
	elapsedTime = (double)(endTime - timer) / CLOCKS_PER_SEC;
}

void Algorithm::ShowMemory()
{
	int size = sizeof(GraphNode);
	size *= elements.size();
	cout << name << " used " << size << " bytes of memory\n";
}

#include "Algorithm.h"

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
		cout << name << " succeded after " << iterations << " iterations: \nand " << elapsedTime.count() << " miliseconds\n";
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
	timer = chrono::system_clock::now();
}

void Algorithm::StopTimer()
{
	elapsedTime = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - timer);
}

void Algorithm::ShowMemory()
{
	int size = sizeof(GraphNode);
	size *= elements.size();
	cout << name << " used " << size << " bytes of memory\n";
}

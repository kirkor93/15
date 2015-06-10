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
		cout << name << " succeded after " << iterations << " iterations: \n";
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

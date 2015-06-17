#pragma once

#include <iostream>
#include <string>
#include <list>
#include <ctime>
#include "GraphNode.h"

using namespace std;

class Algorithm
{
protected:
	list<GraphNode*> elements;
	string name;
	double elapsedTime;
private:
	clock_t timer;

public:
	Algorithm();
	virtual ~Algorithm();
	virtual void Solve(GraphNode *startNode, int maxIterations) = 0;
protected:
	void ShowResult(bool succeded, int iterations, GraphNode *finalNode = nullptr);
	void StartTimer();
	void StopTimer();
	void ShowMemory();
};
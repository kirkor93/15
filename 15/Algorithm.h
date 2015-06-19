#pragma once

#include <iostream>
#include <string>
#include <list>
#include <ctime>
#include <chrono>
#include "GraphNode.h"

using namespace std;

class Algorithm
{
protected:
	list<GraphNode*> elements;
	string name;
	chrono::milliseconds elapsedTime;
private:
	chrono::system_clock::time_point timer;

public:
	virtual ~Algorithm();
	virtual void Solve(GraphNode *startNode, int maxIterations) = 0;
protected:
	void ShowResult(bool succeded, int iterations, GraphNode *finalNode = nullptr);
	void StartTimer();
	void StopTimer();
	void ShowMemory();
};
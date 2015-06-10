#pragma once

#include <iostream>
#include <string>
#include <list>
#include "GraphNode.h"

using namespace std;

class Algorithm
{
protected:
	list<GraphNode*> elements;
	string name;

public:
	virtual ~Algorithm();
protected:
	void ShowResult(bool succeded, int iterations, GraphNode *finalNode = nullptr);
};
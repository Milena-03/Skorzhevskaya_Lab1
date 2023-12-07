#pragma once
#include <fstream>
#include "pipe.h"

using namespace std;
class graph
{
	int id;
public:
	static int maxIdG;
	int IDEntry;
	int IDExit;
	int pipeID;
	int diam;
	void addEdge(int begin, int end, pipe pipe);
	void printG();
	void saveGraph(ofstream& fout);
	void loadGraph(ifstream& fin);
};


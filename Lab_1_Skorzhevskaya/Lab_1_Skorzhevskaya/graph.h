#pragma once
#include <fstream>
#include "pipe.h"

using namespace std;
class edge
{
	int id;
public:
	static int maxIdG;
	int IDEntry;
	int IDExit;
	int pipeID;
	int diam;
	void addEdge(int begin, int end, pipe& pipe);
	void printEdge();
	void saveEdge(ofstream& fout);
	void loadEdge(ifstream& fin);
};


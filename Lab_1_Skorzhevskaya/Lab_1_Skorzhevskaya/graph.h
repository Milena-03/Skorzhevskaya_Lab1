#pragma once
#include <fstream>

using namespace std;
class graph
{
	int id;
public:
	static int maxIdG;
	int IDEntry;
	int IDExit;
	int diam;
	void addEdge(int begin, int end, int weight);
	void printG();
	void saveGraph(ofstream& fout);
	void loadGraph(ifstream& fin);
};


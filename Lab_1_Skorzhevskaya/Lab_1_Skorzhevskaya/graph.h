#pragma once
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
};


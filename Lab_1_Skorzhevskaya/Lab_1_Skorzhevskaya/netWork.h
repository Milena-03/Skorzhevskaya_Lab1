#pragma once
#include <fstream>
#include <map>
#include <vector>
#include "pipe.h"
#include "comprSt.h"

class netWork
{
	map<int, comprSt> groupCS;
	map<int, pipe> groupPipe;
public:
	map<int, comprSt> getCS();
	map<int, pipe> getPipe();
	void addPipe();
	void addCS();
	void printAllObj();
	void editPipe(vector<int> res);
	void editCS(vector<int> res);
	void loadFromFile(ifstream& fin);
	void saveToFile(ofstream& fout);
	void deletePipe(int index);
	void deleteCS(int index);
};


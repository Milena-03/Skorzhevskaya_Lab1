#pragma once
#include <fstream>
#include <map>
#include "pipe.h"
#include "comprSt.h"

class netWork
{
	map<int, comprSt> groupCS;
	map<int, pipe> groupPipe;
public:
	/*void getCS();
	void getPipe();*/
	void loadFromFile(ifstream& fin);
	void saveToFile(ofstream& fout);
};


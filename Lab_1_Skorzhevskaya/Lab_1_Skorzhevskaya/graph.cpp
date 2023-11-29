#include "graph.h"
#include "comprSt.h"
#include <iostream>

using namespace std;
int graph::maxIdG = 1;
void graph::addEdge(int begin, int end, int weight)
{
    id = maxIdG;
    IDExit = begin;
    IDEntry = end;
    diam = weight;
    maxIdG++;
}

void graph::printG()
{
    cout << "\n Edge" << endl;
    cout << "ID: " << id << endl;
    cout << "IDExit: " << IDExit << endl;
    cout << "IDEntry: " << IDEntry << endl;
    cout << "diam: " << diam << endl;
}
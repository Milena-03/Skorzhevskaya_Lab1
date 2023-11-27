#include "graph.h"
#include "comprSt.h"
#include <iostream>

using namespace std;
int graph::maxIdG = 1;
void graph::addEdge(int begin, int end, int weight)
{
    maxIdG++;
    IDExit = begin;
    IDEntry = end;
    diam = weight;
}

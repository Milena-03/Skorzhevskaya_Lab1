#include "graph.h"
#include "comprSt.h"
#include <iostream>
#include <fstream>

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
    cout << "\nEdge" << endl;
    cout << "ID: " << id << endl;
    cout << "IDExit: " << IDExit << endl;
    cout << "IDEntry: " << IDEntry << endl;
    cout << "diam: " << diam << endl;
}

void graph::saveGraph(ofstream& fout) {
    if (fout.is_open()) {
        fout << IDExit << endl << IDEntry
            << endl << diam << endl;
    }

}
void graph::loadGraph(ifstream& fin) {
    id = maxIdG;
    fin >> IDExit;
    fin >> IDEntry;
    fin >> diam;
}
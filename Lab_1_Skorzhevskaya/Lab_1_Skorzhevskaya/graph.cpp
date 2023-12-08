#include "graph.h"
#include "comprSt.h"
#include "pipe.h"
#include <iostream>
#include <fstream>

using namespace std;
int edge::maxIdG = 1;
void edge::addEdge(int begin, int end, pipe& pipe)
{
    id = maxIdG;
    IDExit = begin;
    IDEntry = end;
    pipeID = pipe.getID();
    diam = pipe.diam;
    maxIdG++;
}

void edge::printEdge()
{
    cout << "\nEdge" << endl;
    cout << "ID: " << id << endl;
    cout << "IDExit: " << IDExit << endl;
    cout << "IDEntry: " << IDEntry << endl;
    cout << "pipeID: " << pipeID << endl;
    cout << "diam: " << diam << endl;
}

void edge::saveEdge(ofstream& fout) {
    if (fout.is_open()) {
        fout << IDExit << endl << IDEntry
            << endl << pipeID << endl << diam;
    }

}
void edge::loadEdge(ifstream& fin) {
    id = maxIdG;
    fin >> IDExit;
    fin >> IDEntry;
    fin >> pipeID;
    fin >> diam;
}
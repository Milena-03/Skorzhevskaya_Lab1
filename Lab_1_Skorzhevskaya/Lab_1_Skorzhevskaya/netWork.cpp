#include "netWork.h"
#include "utils.h"
//#include "pushElements.cpp"
//#include "pushPipeE.cpp"
#include<iostream>

void addCS(map<int, comprSt>& groupCS, comprSt newCS) {
    groupCS.insert(pair<int, comprSt>(comprSt::maxCSID, newCS));
    comprSt::maxCSID++;
}
void addPipe(map<int, pipe>& groupPipe, pipe& newPipe) {
    groupPipe.insert(pair<int, pipe>(pipe::maxPipeID, newPipe));
    pipe::maxPipeID++;
}

void netWork::loadFromFile(ifstream& fin)
{
    string marker;
    bool flagP = 0, flagCS = 0;
    groupPipe.erase(groupPipe.begin(), groupPipe.end());
    groupCS.erase(groupCS.begin(), groupCS.end());
    pipe::maxPipeID = 1;
    comprSt::maxCSID = 1;
    if (fin.is_open()) {
        while (!fin.eof() && marker!="G") {
            fin >> marker;
            if (marker == "PIPE") {
                pipe newPipe;
                newPipe.loadPipe(fin);
                addPipe(groupPipe, newPipe);
                flagP = 1;
            }
            if (marker == "CS") {
                comprSt newCS;
                newCS.loadCS(fin);
                addCS(groupCS, newCS);
                flagCS = 1;
            }
        }
        if (!flagP) cout << "save the pipe data to a file" << endl;
        if (!flagCS) cout << "save the CS data to a file" << endl;
    }
    else {
        cout << "Error! The file does not exist" << endl;
    }
}

void netWork::saveToFile(ofstream& fout)
{

}

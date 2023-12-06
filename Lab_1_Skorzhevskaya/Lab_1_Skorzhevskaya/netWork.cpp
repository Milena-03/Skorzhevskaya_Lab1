#include "netWork.h"
#include "utils.h"
//#include "pushElements.cpp"
//#include "pushPipeE.cpp"
#include<iostream>

void paddCS(map<int, comprSt>& groupCS, comprSt newCS) {
    groupCS.insert(pair<int, comprSt>(comprSt::maxCSID, newCS));
    comprSt::maxCSID++;
}
void paddPipe(map<int, pipe>& groupPipe, pipe& newPipe) {
    groupPipe.insert(pair<int, pipe>(pipe::maxPipeID, newPipe));
    pipe::maxPipeID++;
}

map<int, comprSt> netWork::getCS()
{
    return map<int, comprSt>(groupCS);
}

map<int, pipe> netWork::getPipe()
{
    return map<int, pipe>(groupPipe);
}

void netWork::addPipe()
{
    pipe newPipe;
    newPipe.addPipe();
    paddPipe(groupPipe, newPipe);
}

void netWork::addCS()
{
    comprSt newCS;
    newCS.addCS();
    paddCS(groupCS, newCS);
}

void netWork::printAllObj()
{
    if (groupPipe.size() == 0) cout << "Input or load pipe to print" << endl;
    for (auto& [key, p] : groupPipe) {
        cout << "\nPIPE information" << endl;
        p.printPipe();
    }
    if (groupCS.size() == 0) cout << "Input or load CS to print" << endl;
    for (auto& [key, cs] : groupCS) {
        cout << "\nCS information" << endl;
        cs.printCS();
    }
}

void netWork::editPipe(vector<int> res)
{
    for (int i = 0; i < res.size(); i++) {
        groupPipe[res[i]].editPipe();
    }
}

void netWork::editCS(vector<int> res)
{
    for (int i = 0; i < res.size(); i++) {
        groupCS[res[i]].editCS();
    }
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
                paddPipe(groupPipe, newPipe);
                flagP = 1;
            }
            if (marker == "CS") {
                comprSt newCS;
                newCS.loadCS(fin);
                paddCS(groupCS, newCS);
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
    if (groupPipe.size() != 0) {
        for (auto const& pipe : groupPipe) {
            if (groupPipe[pipe.first].km_mark != "") {
                groupPipe[pipe.first].savePipe(fout);
            }
        }
    }
    if (groupCS.size() != 0) {
        for (auto const& CS : groupCS) {
            if (groupCS[CS.first].name != "") {
                groupCS[CS.first].saveCS(fout);
            }
        }
    }
}

void netWork::deletePipe(int index)
{
    groupPipe.erase(index);
}

void netWork::deleteCS(int index)
{
    groupCS.erase(index);
}

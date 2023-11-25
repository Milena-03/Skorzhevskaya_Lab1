#pragma once

#include <string>
#include <fstream>

using namespace std;

class pipe
{
private:
    int id;
public:
    static int maxPipeID;
    pipe();
    int getID() const;
    string km_mark;
    double length;
    int diam;
    bool repair;
    void addPipe();
    void printPipe();
    void editPipe();
    void loadPipe(ifstream& fin);
    void savePipe(ofstream& fout);
};


#pragma once

#include <string>
#include <fstream>

using namespace std;

class pipe
{
private:
    int id;
public:
    int getID() const;
    void setID(int ID);
    string km_mark;
    double length;
    int diam;
    bool repair;
    void addPipe();
    void printPipe();
    //void loadPipe(string FILENAME);
    void loadPipe(ifstream& fin);
    void savePipe(ofstream& fout);
    void editPipe();
};


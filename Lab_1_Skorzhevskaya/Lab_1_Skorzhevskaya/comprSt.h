#pragma once
#include <string>
#include <fstream>

using namespace std;

class comprSt
{
private:
    int id;
public:
    static int maxCSID;
    comprSt();
    int getID() const;
    string name;
    int numOfWS;
    int WSinOperation;
    double efficiency;
    void addCS();
    void printCS();
    void editCS();
    void saveCS(ofstream& fout);
    void loadCS(ifstream& fin);
};


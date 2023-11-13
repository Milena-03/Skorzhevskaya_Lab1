#pragma once
#include <string>
#include <fstream>

using namespace std;

class comprSt
{
private:
    int id;
public:
    int getID() const;
    void setID(int ID);
    string name;
    int numOfWS;
    int WSinOperation;
    double efficiency;
    void printCS();
    void addCS();
    void saveCS(ofstream& fout);
    void loadCS();
    void editCS();
   // void deleteCS(int ID);
};


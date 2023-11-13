#include "pipe.h"
#include <iostream>
#include <fstream>
#include "getValue.cpp"

using namespace std;

int pipe::getID() const
{
    return id;
}

void pipe::setID(int ID)
{
    this->id = ID;
}

void pipe::addPipe()
{
    cout << "Enter the km mark of the pipe:";
    cin >> ws;
    getline(cin, km_mark);
    cout << "Enter the length of the pipe:";
    length = inputT(0.2);
    cout << "Enter the diametr of the pipe:";
    diam = inputT(1);
    cout << "Enter 1 if the pipe is under repair otherwise 0:";
    repair = inputT(true);
}

void pipe::printPipe()
{
    if (km_mark == "") cout << "Input or load data to print" << endl;
    else {
        cout << "id: " << id << endl;
        cout << "km mark: " << km_mark << endl;
        cout << "length: " << length << endl;
        cout << "diametr: " << diam << endl;
        cout << "repair: " << repair << endl;
    }
}

void pipe::loadPipe()
{
    pipe newPipe;
    ifstream fin;
    string marker;
    bool flag = 0;
    fin.open("data.txt", ios::in);

    if (fin.is_open())
    {
        while (!fin.eof()) {
            fin >> marker;
            if (marker == "PIPE") {
                fin >> ws;
                fin >> id;
                getline(fin, km_mark);
                fin >> length;
                fin >> diam;
                fin >> repair;
                fin.close();
                flag = 1;
                break;
            }
        }
        if (!flag) cout << "save the pipe data to a file" << endl;
    }
    else if (!fin.is_open()) {
        cout << "Error! The file data.txt does not exist" << endl;
    }
}

void pipe::savePipe(ofstream& fout)
{
    if (fout.is_open()) {
        fout << "PIPE\n" << km_mark << endl << length
            << endl << diam << endl << repair << endl;
    }
}

void pipe::editPipe()
{
    repair = !repair;
}

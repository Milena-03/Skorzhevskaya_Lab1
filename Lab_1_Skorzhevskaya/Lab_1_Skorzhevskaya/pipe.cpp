#include "pipe.h"
#include <iostream>
#include <fstream>
#include "utils.h"

using namespace std;
int pipe::maxPipeID = 1;

pipe::pipe() {
    id = 0;
    km_mark = "";
    length = 0;
    diam = 0;
    repair = 0;
}

int pipe::getID() const
{
    return id;
}

void pipe::addPipe()
{
    id = maxPipeID;
    cout << "Enter the km mark of the pipe:";
    cin >> ws;
    getline(cin, km_mark);
    cerr << km_mark << endl;
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

void pipe::loadPipe(ifstream& fin)
{
    id = maxPipeID;
    fin >> ws;
    getline(fin, km_mark);
    fin >> length;
    fin >> diam;
    fin >> repair;
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

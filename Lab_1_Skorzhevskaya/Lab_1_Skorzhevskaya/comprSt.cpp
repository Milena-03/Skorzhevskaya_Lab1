#include "comprSt.h"
#include <iostream>
#include <fstream>
#include "getValue.cpp"
#include "check.cpp"

using namespace std;

int comprSt::getID() const
{
	return id;
}

void comprSt::setID(int ID)
{
	this -> id = ID;
}

//добавление КС с консоли
void comprSt::addCS() {
    cout << "Enter the name of the CS:";
    cin >> ws;
    getline(cin, name);
    cout << "Enter the number of WS:";
    numOfWS = inputT(1);
    cout << "Enter the WS in operation:";
    WSinOperation = inputT(1);

    while (1) {
        if (checkNumWSinOperation(WSinOperation, numOfWS)) {
            cout << "Enter a number more than 0 and less than or equal to " << numOfWS << ": ";
            WSinOperation = inputT(1);
        }
        else break;
    }
    cout << "Enter efficiency:";
    efficiency = inputT(0.0);
}
//Вывод КС на консоль
void comprSt::printCS()
{
    if (name == "") cout << "Input or load data to print" << endl;
    else {
        cout << "id: " << getID() << endl;
        cout << "name: " << name << endl;
        cout << "number of WS: " << numOfWS << endl;
        cout << "WS in operation: " << WSinOperation << endl;
        cout << "efficiency: " << efficiency << endl;
    }
}
//Сохранение КС в файл
void comprSt::saveCS(ofstream& fout) {

    if (fout.is_open()) {
        fout << "CS\n" << name << endl << numOfWS
            << endl << WSinOperation << endl << efficiency << endl;
    }
}
//Загрузка КС из файла
void comprSt::loadCS() {
    int id;
    comprSt newCS;
    ifstream fin;
    string marker;
    bool flag = 0;
    fin.open("data.txt", ios::in);
    if (fin.is_open())
    {
        while (!fin.eof()) {
            fin >> marker;
            if (marker == "CS") {
                fin >> ws;
                fin >> id;
                getline(fin, name);
                fin >> numOfWS;
                fin >> WSinOperation;
                fin >> efficiency;
                fin.close();
                flag = 1;
                break;
            }
        }if (!flag) cout << "save the CS data to a file" << endl;
    }
    else if (!fin.is_open()) {
        cout << "Error! The file data.txt does not exist" << endl;
    }
}
//Изменение КС
void comprSt::editCS() {

    cout << "Enter '1' to start one workshop and '0' to stop: " << endl;
    bool sign = inputT(true);
    if (sign == 1) {
        if (WSinOperation == numOfWS) cout << "all workshops are working" << endl;
        else WSinOperation++;
    }
    else {
        if (WSinOperation == 0) cout << "all workshops are stopped" << endl;
        else WSinOperation--;
    }
}

#include "comprSt.h"
#include <iostream>
#include <fstream>

#include "utils.h"
#include "check.cpp"

using namespace std;

int comprSt::maxCSID = 1;

comprSt::comprSt() {
    id = 0;
    name = "";
    numOfWS = 0;
    WSinOperation = 0;
    efficiency = 0;
}

int comprSt::getID() const
{
	return id;
}

//добавление КС с консоли
void comprSt::addCS() {
    id = maxCSID;
    cout << "Enter the name of the CS:";
    cin >> ws;
    getline(cin, name);
    cerr << name << endl;
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
//Сохранение КС в файл
void comprSt::saveCS(ofstream& fout) {

    if (fout.is_open()) {
        fout << "CS\n" << name << endl << numOfWS
            << endl << WSinOperation << endl << efficiency << endl;
    }
}
//Загрузка КС из файла
void comprSt::loadCS(ifstream& fin) {
                
    id = maxCSID;
    fin >> ws;
    getline(fin, name);
    fin >> numOfWS;
    fin >> WSinOperation;
    fin >> efficiency;
}

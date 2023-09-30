﻿#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct pipe
{
    string km_mark;
    double length;
    int diam;
    bool repair;
};

struct comprSt 
{
    string name;
    int numOfWS;
    int WSinOperation;
    double efficiency;
};

//---------------ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ-----------------//
//получение индекса 1 или 0 для св-ва "в ремонте"
bool inputBool() {

    bool state;
    while (!(cin >> state)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Try again: ";
    } 
    return state;
}

int inputInt() {
    int intValue;

    while (!(cin >> intValue)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Try again: ";
    }
    return intValue;
}

double inputDouble() {
    double doubleValue;
    while (!(cin >> doubleValue)) {
      
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Try again: ";
    }
    return doubleValue;
}

int SaveInformation() {
    int saveItem;
    cout << "Select an option\n1. save the pipe\n2. save the CS\n3. save all" << endl;
    cin >> saveItem;
    return saveItem;
}

bool checkNumWSinOperation(int checkValue, int numWS) {
    if (checkValue > numWS) return 1;
    else return 0;
}

//------------------ЗАГРУЗКА ИЗ ФАЙЛА----------------------//

//загрузкa информации о трубе из файла
pipe loadPipe() {

    pipe newPipe;
    ifstream fin;
   
    fin.open("dataPipe.txt", ios::in);

    if (fin.is_open() && fin.eof())
    {
        fin >> newPipe.km_mark;
        fin >> newPipe.length;
        fin >> newPipe.diam;
        fin >> newPipe.repair;
        fin.close();
    }
    else if (!fin.eof()) {

        cout << "File dataPipe.txt empty" << endl;
    }
    else {
        cout << "Error! The file dataPipe.txt does not exist" << endl;
    }
    return newPipe;
}
//загрузкa информации о КС из файла
comprSt loadCS() {

    comprSt newCS;
    ifstream fin;
    fin.open("dataCS.txt", ios::in);
    if (fin.is_open() && !fin.eof())
    {
        //fin >> newCS.name;
        getline(fin, newCS.name, ';');
        fin >> newCS.numOfWS;
        fin >> newCS.WSinOperation;
        fin >> newCS.efficiency;
        fin.close();
    }
    else if (fin.eof()) {
        cout << "File dataCS.txt empty" << endl;
    }
    else {
        cout << "Error! The file dataCS.txt does not exist" << endl;
    }
    
    return newCS;
}
//-------------------СОХРАНЕНИЕ В ФАЙЛ-------------------------//

//Сохранение информации о трубе в файл
void savePipe(const pipe& pipe) {

    ofstream fout;
    fout.open("dataPipe.txt", ios::out);
    if (fout.is_open()) {
        if (pipe.km_mark == "") cout << "Input or load data to save" << endl;
        else {
            fout << pipe.km_mark << endl << pipe.length
                << endl << pipe.diam << endl << pipe.repair << endl;
            fout.close();
        }
    }
    fout.close();
}
//Сохранение информации о КС в файл
void saveCS(const comprSt& CS) {

    ofstream fout;
       fout.open("dataCS.txt", ios::out);
    if (fout.is_open()){
        if (CS.name== "") cout << "Input or load data to save" << endl;
        else{
            fout << CS.name << endl << CS.numOfWS
                << endl << CS.WSinOperation << endl<< CS.efficiency << endl;
            fout.close();
        }
    }
    fout.close();
}

void SaveToFile(const pipe& pipe, const comprSt& CS) {
    int i = SaveInformation();
    switch (i) {
    case 1: {
        savePipe(pipe);
        break;
    }
    case 2: {
        saveCS(CS);
        break;
    }
    case 3: {
        savePipe(pipe);
        saveCS(CS);
        break;
    }
    default: {
        cout << "wrong action" << endl;
    }
    }
}

//---------------------ВВОД С КОНСОЛИ-------------------------//

//Ввод информации о трубе с консоли
pipe inputPipe() {

    pipe newPipe;
    cout << "Enter the km mark of the pipe:";
    cin >> ws;
    getline(cin, newPipe.km_mark);
    cout << "Enter the length of the pipe:";
    newPipe.length = inputDouble();
    cout << "Enter the diametr of the pipe:";
    newPipe.diam = inputInt();
    cout << "Enter 1 if the pipe is under repair otherwise 0:";
    newPipe.repair = inputBool();
    return newPipe;
}
//Ввод информации о КС с консоли
comprSt inputCS() {

    comprSt newCS;

    cout << "Enter the name of the CS:";
    cin >> ws;
    getline(cin, newCS.name);
    //!!my ks 

    cout << "Enter the number of WS:";
    newCS.numOfWS = inputInt();

    cout << "Enter the WS in operation:";
    newCS.WSinOperation = inputInt();

    while (1) {
        if (checkNumWSinOperation(newCS.WSinOperation, newCS.numOfWS)) {
            cout << "Enter a number less than or equal to " << newCS.numOfWS << ": ";
            newCS.WSinOperation = inputInt();
        }
        else break;
    }

    cout << "Enter efficiency:";
    newCS.efficiency = inputDouble();
    return newCS;
}

//--------------------ВЫВОД НА КОНСОЛЬ-------------------//

//Вывод информации о трубе на консоль
void printPipe(const pipe &pipe) {
    if (pipe.km_mark == "") cout << "Input or load data to print" << endl;
    else {
        cout << "km mark: " << pipe.km_mark << endl;
        cout << "length: " << pipe.length << endl;
        cout << "diametr: " << pipe.diam << endl;
        cout << "repair: " << pipe.repair << endl;
    }
}

//Вывод информации о КС на консоль
void printCS(const comprSt &CS) {
    if (CS.name == "") cout << "Input or load data to save" << endl;
    else {
        cout << "name: " << CS.name << endl;
        cout << "number of WS: " << CS.numOfWS << endl;
        cout << "WS in operation: " << CS.WSinOperation << endl;
        cout << "efficiency: " << CS.efficiency << endl;
    }
}

void printAllObj(const pipe& pipe, const comprSt& CS) {
    cout << "\nPipe information" << endl;
    printPipe(pipe);
    cout << "\nCS information" << endl;
    printCS(CS);
}

//--------------РЕДАКТИРОВАНИЕ ЭЛЕМЕНТОВ-----------------//

//функция изменения признака "в ремонте"
void changeRepair(pipe& pipe) {
    pipe.repair = inputBool();
}
//функция запуска/останова цеха
void editCS(comprSt& CS) {
    cout << "Enter '1' to start one workshop and '0 to stop: " << endl;
    bool sign = inputBool();
    if (sign == 1) {
        if (CS.WSinOperation == CS.numOfWS) cout << "all workshops are working" << endl;
        else CS.WSinOperation ++;
    }
    else{
        if (CS.WSinOperation == 0) cout << "all workshops are stopped" << endl;
        else CS.WSinOperation --;
    }
}



//-----------МЕНЮ------------//
void printMenu() {
    cout << "1. Input pipe" << endl
        << "2. Input CS" << endl
        << "3. View all items" << endl
        << "4. Edit pipe" << endl
        << "5. Edit CS" << endl
        << "6. Save to file" << endl
        << "7, Load from file" << endl
        << "0. Exit" << endl;
}

int main()
{
    pipe newPipe;
    comprSt newCS;
    while (1)
    {
        printMenu();
        int i = inputInt();
        switch (i)
        {
        case 1:
        {
            newPipe = inputPipe();
            break;
        }
        case 2:
        {
            newCS = inputCS();
            break;
        }
        case 3:
        {
            printAllObj(newPipe, newCS);
            break;
        }
        case 4:
        {
            cout << "enter 1 or 0 to change state" << endl;
            newPipe.repair = inputBool();
            break;
        }
        case 5:
        {
            /*cout << "Enter '+' to start one workshop and '-' to stop: " << endl;
            string sign;
            cin >> sign;*/
            editCS(newCS);
            break;
        }
        case 6:
        {
            SaveToFile(newPipe, newCS);
            break;
        }
        case 7:
        {
            newPipe = loadPipe();
            newCS = loadCS();
            break;
        }
        case 0:
        {
            return 0;
        }
        default:
        {
            cout << "Wrong action" << endl;
        }
        }
    }
    
    return 0;
}
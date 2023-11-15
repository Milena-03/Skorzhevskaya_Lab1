#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
//#include <typeinfo>
#include "comprSt.h"
#include "pipe.h"
#include "getValue.cpp"
using namespace std;



void printMenu() {
    cout << "\n1. Input pipe" << endl
        << "2. Input CS" << endl
        << "3. View all items" << endl
        << "4. Edit pipe" << endl
        << "5. Edit CS" << endl
        << "6. Save to file" << endl
        << "7. Load from file" << endl
        << "8. Delete pipe" << endl
        << "9. Delete CS" << endl
        << "0. Exit" << endl
        << "Choose action: ";
}

//
///*
//struct pipe
//{
//    int id;
//    string km_mark;
//    double length;
//    int diam;
//    bool repair;
//};*/
//
////struct comprSt 
////{
////    int id;
////    string name;
////    int numOfWS;
////    int WSinOperation;
////    double efficiency;
////};
//
////---------------ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ-----------------//
//
////template <typename T>
//
////T inputT(T value) {
////
////    T state;
////    while (!(cin >> state)) {
////        cin.clear();
////        cin.ignore(1000, '\n');
////        cout << "Try again: ";
////    }
////    return state;
////}
///*T inputT(T value) {
//
//    T state;
//    while(1){
//        if (!(cin >> state)) {
//            cin.clear();
//            cin.ignore(1000, '\n');
//            cout << "Try again: ";
//        }
//        else if (state >= 0) {
//            return state;
//        }
//        else cout << "enter value more than 0: ";
//    }
//    return state;
//}*/
//
///**************************************************************
//bool checkNumWSinOperation(int checkValue, int numWS) {
//    if ((checkValue > numWS) || (checkValue < 0)) return 1;
//    else return 0;
//}****************************************************************/
//
////------------------ВЫБОР ТРУБЫ/КС -------------------------//
//
////pipe& SelectPipe(map<int, pipe> groupPipe) {
////    while (1) {
////        unsigned int index = inputT(1);
////        if (index >= 0u && index < groupPipe.size()) {
////            return groupPipe[index];
////        }
////        cout << "enter correct number" << endl;
////    }
////
////}
int SelectPipe(map<int, pipe> groupPipe) {
    cout << "enter pipe id: ";
    while (1) {
        unsigned int index = inputT(1);
        if (index >= 0 && index < groupPipe.size()) {
            return index;
        }
        cout << "enter correct number: ";
    }

}

////comprSt& SelectCS(map<int, comprSt> groupCS) {
////    while (1) {
////        cout << "Select pipe\n";
////        unsigned int index = inputT(1);
////        if (index >= 0 && index < groupCS.size()) {
////            return groupCS[index];
////        }
////        cout << "enter correct number" << endl;
////    }
////
////}
int SelectCS(map<int, comprSt> groupCS) {
    cout << "Select CS id: ";
    while (1) {
        unsigned int index = inputT(1);
        if (index >= 0 && index < groupCS.size()) {
            return index;
        }
        cout << "enter correct number: ";
    }

}

vector<int> findPipebyName(map<int, pipe>& groupPipe, string name) {
    vector <int> res;

    for (int i = 0; i < groupPipe.size(); i++) {
        if (groupPipe[i].km_mark == name)
            res.push_back(i);
    }
    return res;
}
vector<int> findCSbyName(map<int, comprSt>& groupCS, string name) {
    vector <int> res;

    for (int i = 0; i < groupCS.size(); i++) {
        if (groupCS[i].name == name)
            res.push_back(i);
    }
    return res;
}
vector<int> findPipebyRepair(map<int, pipe>& groupPipe, bool repair) {
    vector <int> res;

    for (int i = 0; i < groupPipe.size(); i++) {
        if (groupPipe[i].repair == repair)
            res.push_back(i);
    }
    return res;
}
vector<int> findCSbyPer(map<int, comprSt>& groupCS, int per) {
    vector <int> res;

    for (int i = 0; i < groupCS.size(); i++) {
        int k = round((100.0 * (groupCS[i].numOfWS - groupCS[i].WSinOperation)) / groupCS[i].numOfWS);
        if (k == per)
            res.push_back(i);
    }
    return res;
}

////------------------ЗАГРУЗКА ИЗ ФАЙЛА----------------------//
//
////загрузкa информации о трубе из файла
//pipe loadPipe() {
//
//    pipe newPipe;
//    ifstream fin;
//    string marker;
//    bool flag = 0;  
//    fin.open("data.txt", ios::in);
//
//    if (fin.is_open())
//    {
//        while (!fin.eof()) {
//            fin >> marker;
//            if (marker == "PIPE") {
//                fin >> ws;
//                fin >> newPipe.id;
//                getline(fin, newPipe.km_mark);
//                fin >> newPipe.length;
//                fin >> newPipe.diam;
//                fin >> newPipe.repair;
//                fin.close();
//                flag = 1;
//                break;
//            }
//        }
//        if (!flag) cout << "save the pipe data to a file" << endl;
//    }
//    else if (!fin.is_open()) {
//        cout << "Error! The file data.txt does not exist" << endl;
//    }
//    return newPipe;
//}
////загрузкa информации о КС из файла
///*********************************************************************
//comprSt loadCS() {
//    int id;
//    comprSt newCS;
//    ifstream fin;
//    string marker;
//    bool flag = 0;
//    fin.open("data.txt", ios::in);
//    if (fin.is_open())
//    {
//        while (!fin.eof()) {
//            fin >> marker;
//            if (marker == "CS") {
//                fin >> ws;
//                fin >> id;
//                newCS.setID(id);
//                getline(fin, newCS.name);
//                fin >> newCS.numOfWS;
//                fin >> newCS.WSinOperation;
//                fin >> newCS.efficiency;
//                fin.close();
//                flag = 1;
//                break;
//            }
//        }if (!flag) cout << "save the CS data to a file" << endl;
//    }
//    else if (!fin.is_open()) {
//        cout << "Error! The file data.txt does not exist" << endl;
//    }
//    return newCS;
//}*******************************************************************/
//
////-------------------СОХРАНЕНИЕ В ФАЙЛ-------------------------//
//
////Сохранение информации о трубе в файл
//void savePipe(const pipe& pipe, ofstream& fout) {
//
//   //ofstream fout;
//   //fout.open("data.txt", ios::out);
//   if (fout.is_open()) {
//            fout << "PIPE\n" << pipe.km_mark << endl << pipe.length
//                << endl << pipe.diam << endl << pipe.repair << endl;
//           // fout.close();
//   }
//}
////Сохранение информации о КС в файл
///*********************************************************************
//void saveCS(const comprSt& CS, ofstream& fout) {
//
//    //ofstream fout;
//    //fout.open("data.txt", ios::app);
//    if (fout.is_open()){
//            fout << "CS\n" << CS.name << endl << CS.numOfWS
//                << endl << CS.WSinOperation << endl<< CS.efficiency << endl;
//           // fout.close();
//    }
//}*****************************************************************/
////void savePipe(map<int, pipe> groupPipe, ofstream& fout) {
////
////   //ofstream fout;
////   //fout.open("data.txt", ios::out);
////   int index = SelectPipe(groupPipe)
////   if (fout.is_open()) {
////            fout << "PIPE\n" << groupPipe[index].km_mark << endl << groupPipe[index].length
////                << endl << groupPipe[index].diam << endl << groupPipe[index].repair << endl;
////           // fout.close();
////   }
////}
//////Сохранение информации о КС в файл
////void saveCS(map<int, comprSt> groupCS, ofstream& fout) {
////
////    int index = SelectCS(groupCS)
////    if (fout.is_open()){
////            fout << "CS\n" << groupCS[index].name << endl << groupCS[index].numOfWS
////                << endl << groupCS[index].WSinOperation << endl<< groupCS[index].efficiency << endl;
////           // fout.close();
////    }
////}
//
////void SaveToFile(const pipe& pipe, const comprSt& CS) {
////    //ofstream fout;
////    //fout.open("data.txt", ios::out);
////    
////    if ((CS.name == "") || (pipe.km_mark == "")) cout << "Input or load data to save" << endl;
////    else {
////        /*if (fout.is_open()) {
////            fout << "PIPE\n" << pipe.km_mark << endl << pipe.length
////                << endl << pipe.diam << endl << pipe.repair << endl;
////            fout << "CS\n" << CS.name << endl << CS.numOfWS
////                << endl << CS.WSinOperation << endl << CS.efficiency << endl;
////            fout.close();
////
////
////        }*/
////        savePipe(pipe);
////        saveCS(CS);
////    }
////
////        /*if ((CS.name == "") && (pipe.km_mark == "")) cout << "Input or load data to save" << endl;
////        else {
////            if ((CS.name == "") && (pipe.km_mark != "")) {
////                savePipe(pipe);
////                cout << "Input or load CS data to save" << endl;
////            }
////            else if ((CS.name != "") && (pipe.km_mark == "")) {
////                saveCS(CS);
////                cout << "Input or load pipe data to save" << endl;
////            }
////            else {
////                saveCS(CS);
////                savePipe(pipe);    
////            }
////        }*/
////}
//
////void SaveToFile(const pipe& pipe, const comprSt& CS) {
////    //ofstream fout;
////    //fout.open("data.txt", ios::out);
////
////    if ((CS.name == "") && (pipe.km_mark == "")) cout << "Input or load data to save" << endl;
////    else {
////        ofstream fout("data.txt");
////        /*ofstream fout;
////        fout.open("data.txt", ios::app);*/
////        if (CS.name == "") {
////            savePipe(pipe, fout);
////        }
////        else if (pipe.km_mark == "") {
////            saveCS(CS, fout);
////        }
////        else {
////            savePipe(pipe, fout);
////            saveCS(CS, fout);
////        }
////        fout.close();
////    }
////}
void SaveToFile(map<int, pipe> groupPipe, map<int, comprSt> groupCS) {
    //ofstream fout;
    //fout.open("data.txt", ios::out);

    if (groupPipe.size() == 0 && groupCS.size()==0) cout << "Input or load data to save" << endl;
    else {
        
        ofstream fout("data.txt");
        /*ofstream fout;
        fout.open("data.txt", ios::app);*/
        /*if (groupCS.size() == 0) {
            savePipe(pipe, fout);
        }
        else if (groupCS.size() == 0) {
            saveCS(CS, fout);
        }
        else {
            savePipe(pipe, fout);
            saveCS(CS, fout);
        }*/
        if (groupPipe.size() != 0) {
            int indPipe = SelectPipe(groupPipe);
            pipe pipe = groupPipe[indPipe];
            //savePipe(pipe, fout);
            pipe.savePipe(fout);
        }
        if (groupCS.size() != 0) {
            int indCS = SelectCS(groupCS);
            comprSt CS = groupCS[indCS];
            //saveCS(CS, fout);
            CS.saveCS(fout);
        }
        fout.close();
    }
}

////---------------------ВВОД С КОНСОЛИ-------------------------//
//
//istream& operator >> (istream& in, pipe& newPipe) {
//    cout << "Enter the km mark of the pipe:";
//    in >> ws;
//    getline(in, newPipe.km_mark);
//    cout << "Enter the length of the pipe:";
//    //newPipe.length = inputDouble();
//    newPipe.length = inputT(0.2);
//    cout << "Enter the diametr of the pipe:";
//    //newPipe.diam = inputInt();
//    newPipe.diam = inputT(1);
//    cout << "Enter 1 if the pipe is under repair otherwise 0:";
//    newPipe.repair = inputT(true);
//    //return newPipe;
//    return in;
//}
//
////Ввод информации о трубе с консоли
///*pipe inputPipe() {
//
//    pipe newPipe;
//    cout << "Enter the km mark of the pipe:";
//    cin >> ws;
//    getline(cin, newPipe.km_mark);
//    cout << "Enter the length of the pipe:";
//    newPipe.length = inputT(0.0);
//    cout << "Enter the diametr of the pipe:";
//    newPipe.diam = inputT(1);
//    cout << "Enter 1 if the pipe is under repair otherwise 0:";
//    newPipe.repair = inputT(true);
//    return newPipe;
//}*/
//
////Ввод информации о КС с консоли
///************************************************************************
//istream& operator >> (istream& in, comprSt& newCS) {
//    cout << "Enter the name of the CS:";
//    cin >> ws;
//
//    getline(cin, newCS.name);
//
//    cout << "Enter the number of WS:";
//    newCS.numOfWS = inputT(1);
//
//    cout << "Enter the WS in operation:";
//    newCS.WSinOperation = inputT(1);
//
//    while (1) {
//        if (checkNumWSinOperation(newCS.WSinOperation, newCS.numOfWS)) {
//            cout << "Enter a number more than 0 and less than or equal to " << newCS.numOfWS << ": ";
//            newCS.WSinOperation = inputT(1);
//        }
//        else break;
//    }
//
//    cout << "Enter efficiency:";
//    newCS.efficiency = inputT(0.0);
//    return in;
//}
//**************************************************************************/
///*comprSt inputCS() {
//
//    comprSt newCS;
//
//    cout << "Enter the name of the CS:";
//    cin >> ws;
//    getline(cin, newCS.name);
//
//    cout << "Enter the number of WS:";
//    newCS.numOfWS = inputT(1);
//
//    cout << "Enter the WS in operation:";
//    newCS.WSinOperation = inputT(1);
//
//    while (1) {
//        if (checkNumWSinOperation(newCS.WSinOperation, newCS.numOfWS)) {
//            cout << "Enter a number less than or equal to " << newCS.numOfWS << ": ";
//            newCS.WSinOperation = inputT(1);
//        }
//        else break;
//    }
//
//    cout << "Enter efficiency:";
//    newCS.efficiency = inputT(0.0);
//    return newCS;
//}*/
//
////--------------------ВЫВОД НА КОНСОЛЬ-------------------//
//
//ostream& operator << (ostream& out, const pipe& pipe) {
//    if (pipe.km_mark == "") cout << "Input or load data to print" << endl;
//    else {
//        out << "id: " << pipe.id << endl;
//        out << "km mark: " << pipe.km_mark << endl;
//        out << "length: " << pipe.length << endl;
//        out << "diametr: " << pipe.diam << endl;
//        out << "repair: " << pipe.repair << endl;
//    }
//    return out;
//}
///************************************************************************
//ostream& operator << (ostream& out, const comprSt& CS) {
//    if (CS.name == "") cout << "Input or load data to print" << endl;
//    else {
//        out << "id: " << CS.getID() << endl;
//        out << "name: " << CS.name << endl;
//        out << "number of WS: " << CS.numOfWS << endl;
//        out << "WS in operation: " << CS.WSinOperation << endl;
//        out << "efficiency: " << CS.efficiency << endl;
//    }
//    return out;
//}
//************************************************************************/
//
//////Вывод информации о трубе на консоль
////void printPipe(const pipe &pipe) {
////    if (pipe.km_mark == "") cout << "Input or load data to print" << endl;
////    else {
////        cout << "id: " << pipe.id << endl;
////        cout << "km mark: " << pipe.km_mark << endl;
////        cout << "length: " << pipe.length << endl;
////        cout << "diametr: " << pipe.diam << endl;
////        cout << "repair: " << pipe.repair << endl;
////    }
////}
////
//////Вывод информации о КС на консоль
////void printCS(const comprSt &CS) {
////    if (CS.name == "") cout << "Input or load data to print" << endl;
////    else {
////        cout << "name: " << CS.name << endl;
////        cout << "number of WS: " << CS.numOfWS << endl;
////        cout << "WS in operation: " << CS.WSinOperation << endl;
////        cout << "efficiency: " << CS.efficiency << endl;
////    }
////}
//
///*void printAllObj(const pipe& pipe, const comprSt& CS) {
//    cout << "\nPipe information" << endl;
//    //printPipe(pipe);
//
//    cout << pipe;
//    cout << "\nCS information" << endl;
//    printCS(CS);
//}*/

void printAllObj(map<int, pipe> groupPipe, map<int, comprSt> groupCS) {
    //cout << "\nPipe information" << endl;
    //printPipe(pipe);
    if (groupPipe.size() ==0) cout << "Input or load pipe to print" << endl;
    for (int i = 0; i < groupPipe.size(); i++) {
        cout << "\nPipe information" << endl;
        //cout << groupPipe[i];
        groupPipe[i].printPipe();
    }
    if (groupCS.size() == 0) cout << "Input or load CS to print" << endl;
    for (int i = 0; i < groupCS.size(); i++) {
        cout << "\nCS information" << endl;
        //cout << groupCS[i];
        groupCS[i].printCS();
    }
}

////--------------РЕДАКТИРОВАНИЕ ЭЛЕМЕНТОВ-----------------//
//
////функция изменения признака "в ремонте"
////pipe changeRepair(pipe& pipe) {
////    pipe.repair = !pipe.repair;
////
////}
//void changeRepair(map<int, pipe> &groupPipe) {
//    int index = SelectPipe(groupPipe);
//    groupPipe[index].repair = !groupPipe[index].repair;
//}
//
////функция запуска/останова цеха
////void editCS(comprSt& CS) {
////    if (CS.name != "") {
////        cout << "Enter '1' to start one workshop and '0 to stop: " << endl;
////        bool sign = inputT(true);
////        if (sign == 1) {
////            if (CS.WSinOperation == CS.numOfWS) cout << "all workshops are working" << endl;
////            else CS.WSinOperation++;
////        }
////        else {
////            if (CS.WSinOperation == 0) cout << "all workshops are stopped" << endl;
////            else CS.WSinOperation--;
////        }
////    }
////    else cout << "Input or load data CS to edit" << endl;
////    
////}
///************************************************************************
//void editCS(map<int, comprSt>& groupCS) {
//
//    int index = SelectCS(groupCS);
//    cout << "Enter '1' to start one workshop and '0' to stop: " << endl;
//    bool sign = inputT(true);
//    if (sign == 1) {
//        if (groupCS[index].WSinOperation == groupCS[index].numOfWS) cout << "all workshops are working" << endl;
//        else groupCS[index].WSinOperation++;
//    }
//    else {
//        if (groupCS[index].WSinOperation == 0) cout << "all workshops are stopped" << endl;
//        else groupCS[index].WSinOperation--;
//    }   
//}
//***************************************************************************/
//-----------МЕНЮ------------//

//----------------ДОБАВЛЕНИЕ ТРУБЫ/КС В MAP------------------------//

void pushBackPipe(map<int, pipe> &groupPipe, pipe newPipe) {
    if (groupPipe.empty()) {
        newPipe.setID(0);
        groupPipe[0] = newPipe;
        return;
    }
    //map<int, pipe>::iterator itEnd;
    //itEnd = groupPipe.end();
    int key = groupPipe.rbegin()->first;
    newPipe.setID(key + 1);
    groupPipe[key+1] = newPipe;
    /*for (int i = 0; i < groupPipe.size()+1; i++) {
        if (groupPipe.count(i) != 0) {
            continue;
        }
        else {
            groupPipe[i] = newPipe;
            return;
        }
    }*/
}
void pushBackCS(map<int, comprSt> &groupCS, comprSt newCS) {
    if (groupCS.empty()) {
        newCS.setID(0);
        groupCS[0] = newCS;
        return;
    }
    
    int key = groupCS.rbegin()->first;
    newCS.setID(key + 1);
    //newCS.id = key + 1;
    groupCS[key+1] = newCS;
}

//-------------------УДАЛЕНИЕ ТРУБЫ/КС--------------------//
void deletePipe(map<int, pipe> &groupPipe) {
    int index = SelectPipe(groupPipe);
    groupPipe.erase(index);
}

void deleteCS(map<int, comprSt> &groupCS) {
    int index = SelectCS(groupCS);
    groupCS.erase(index);
}

void editPipeByName(map<int, pipe>& groupPipe) {

    string nameToSearch;
    cout << "Enter name to search for pipes: ";
    cin >> ws;
    getline(cin, nameToSearch);
    vector<int> res = findPipebyName(groupPipe, nameToSearch);
    if (res.size() == 0) {
        cout << "There are no pipes with this name.\n";
        return;
    }
    for (int i = 0; i < res.size(); i++) {
        groupPipe[res[i]].editPipe();
    }
}

void editPipeByRepair(map<int, pipe>& groupPipe) {
    bool state;
    cout << "Enter repair state to search for pipes: ";
    state = inputT(true);
    vector<int> res = findPipebyRepair(groupPipe, state);
    if (res.size() == 0) {
        cout << "There are no pipes with this repair state.\n";
        return;
    }
    for (int i = 0; i < res.size(); i++) {
        groupPipe[res[i]].editPipe();
    }
}

void editCSByName(map<int, comprSt>& groupCS) {
    cout << "Enter name to search for CS: ";
    string nameToSearch;
    cin >> ws;
    getline(cin, nameToSearch);
    vector<int> res = findCSbyName(groupCS, nameToSearch);
    if (res.size() == 0) {
        cout << "There are no CS with this name.\n";
        return;
    }
    for (int i = 0; i < res.size(); i++) {
        groupCS[res[i]].editCS();
    }
}

void editCSByPer(map<int, comprSt>& groupCS) {
    cout << "Enter persent to search for pipes: ";
    int per;
    per = inputT(1);
    vector<int> res = findCSbyPer(groupCS, per);
    if (res.size() == 0) {
        cout << "There are no CS with this percent.\n";
        return;
    }
    for (int i = 0; i < res.size(); i++) {
        groupCS[res[i]].editCS();
    }
}

int main()
{
    /*pipe newPipe;
    comprSt newCS;*/

    map<int, comprSt> groupCS;
    map<int, pipe> groupPipe;

    while (1)
    {
        printMenu();
        int i = inputT(9);
        switch (i)
        {
        case 1:
        {
            pipe newPipe;
            //newPipe = inputPipe();
            //cin >> newPipe1;
            newPipe.addPipe();
            pushBackPipe(groupPipe, newPipe);
            break;
        }
        case 2:
        {
            comprSt newCS;
            //cin >> newCS;
            newCS.addCS();
            pushBackCS(groupCS, newCS);
            break;
        }
        case 3:
        {
            printAllObj(groupPipe, groupCS);
           //printAllObj(newPipe, newCS);
           // cout << SelectPipe(groupPipe) << endl;
            break;
        }
        case 4:
        {
            /*if (newPipe.km_mark != "") changeRepair(newPipe);
            else cout << "Input or load data pipe to edit" << endl;*/
            if (groupPipe.size() != 0) {
                /*//changeRepair(groupPipe);
                int index = SelectPipe(groupPipe);
                groupPipe[index].editPipe();*/
                
                cout << "Enter 0 to search by name or 1 to search by repair: ";
                bool field = inputT(true);
                if (field == 0) {
                    /*string nameToSearch;
                    cout << "Enter name to search for pipes: ";
                    getline(cin, nameToSearch);
                    vector<int> res = findPipebyName(groupPipe, nameToSearch);
                    if (res.size() == 0) {
                        cout << "There are no pipes with this name.\n";
                        break;
                    }
                    for (int i = 0; i < res.size(); i++) {
                        groupPipe[res[i]].editPipe();
                    }*/
                    editPipeByName(groupPipe);
                }
                else {
                    editPipeByRepair(groupPipe);
                }
            }
            else cout << "Input or load pipe data to edit" << endl;
            break;
        }
        case 5:
        {
            if (groupCS.size() != 0){

            //    int index = SelectCS(groupCS);
            //    groupCS[index].editCS();
            //    //editCS(groupCS);
            
                cout << "Enter 0 to search by name or 1 to search by percent: ";
                bool field = inputT(true);
                if (field == 0) {
                    editCSByName(groupCS);
                }
                else {
                    editCSByPer(groupCS);
                }
            }
            else cout << "Input or load CS data to edit" << endl;
            break;
        }
        case 6:
        {
            SaveToFile(groupPipe, groupCS);
            break;
        }
        case 7:
        {
            //newPipe = loadPipe();
            //newCS = loadCS();
            /*newPipe.loadPipe();
            newCS.loadCS();*/
            int indexP = SelectPipe(groupPipe);
            groupPipe[indexP].loadPipe();
            int indexCS = SelectCS(groupCS);
            groupCS[indexCS].loadCS();
            break;
        }
        /*case 8:
        {
            for (int i : findPipebyName(groupPipe, "kkk"))
                groupPipe[i].printPipe();
            break;
        }
        case 9:
        {
            for (int i : findCSbyPer(groupCS, 38))
                groupCS[i].printCS();
            break;
        }*/
        case 9:
        {
            deletePipe(groupPipe);
            break;
        }
        case 10:
        {
            deleteCS(groupCS);
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

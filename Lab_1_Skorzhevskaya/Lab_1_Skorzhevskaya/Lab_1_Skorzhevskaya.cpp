#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <unordered_set>
#include "comprSt.h"
#include "pipe.h"
#include "utils.h"
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

//--------------------------ВЫБОР ТРУБЫ/КС--------------------------//
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

//--------------ПОИСК ТРУБ/КС ПО ЗАДАННОМУ ФИЛЬТРУ-------------------//
vector<int> findPipebyName(map<int, pipe>& groupPipe, string name) {
    vector <int> res;

    for (int i = 0; i < groupPipe.size(); i++) {
        if (groupPipe[i].km_mark == name)
            res.push_back(i);
    }
    return res;
}
vector<int> findPipeByDiam(map<int, pipe>& groupPipe, int diam) {
    vector <int> res;

    for (int i = 0; i < groupPipe.size(); i++) {
        if (groupPipe[i].diam == diam)
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
vector<int> findCSbyName(map<int, comprSt>& groupCS, string name) {
    vector <int> res;

    for (int i = 0; i < groupCS.size(); i++) {
        if (groupCS[i].name == name)
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

void pushPipe(map<int, pipe>& groupPipe, pipe& newPipe) {
    groupPipe.insert(pair<int, pipe>(pipe::maxPipeID, newPipe));
    pipe::maxPipeID++;
}

void pushCS(map<int, comprSt>& groupCS, comprSt newCS) {
    groupCS.insert(pair<int, comprSt>(comprSt::maxCSID, newCS));
    comprSt::maxCSID++;
}

void loadFromFile(map<int, pipe>& groupPipe, map<int, comprSt>& groupCS) {
    string FILENAME, marker;
    cout << "Enter name of file to load:";
    cin >> FILENAME;
    cerr << FILENAME << endl;
    ifstream fin(FILENAME);
    bool flagP = 0, flagCS = 0;
    groupPipe.erase(groupPipe.begin(), groupPipe.end());
    groupCS.erase(groupCS.begin(), groupCS.end());
    pipe::maxPipeID = 1;
    comprSt::maxCSID = 1;
    if(fin.is_open()){
        while (!fin.eof()) {
            fin >> marker;
            if (marker == "PIPE") {
                pipe newPipe;
                newPipe.loadPipe(fin);
                pushPipe(groupPipe, newPipe);
                flagP = 1;
            }
            if (marker == "CS") {
                comprSt newCS;
                newCS.loadCS(fin);
                pushCS(groupCS, newCS);
                flagCS = 1;
            }
        }
        if (!flagP) cout << "save the pipe data to a file" << endl;
        if (!flagCS) cout << "save the CS data to a file" << endl;
    }else {
        cout << "Error! The file " << FILENAME <<" does not exist" << endl;
    }
}

//------------------------СОХРАНЕНИЕ В ФАЙЛ-----------------------------//
void SaveToFile(map<int, pipe> groupPipe, map<int, comprSt> groupCS) {

    if (groupPipe.size() == 0 && groupCS.size()==0) cout << "Input or load data to save" << endl;
    else {
        string FILENAME;
        cout << "Enter name of file to save:";
        cin >> FILENAME;
        cerr << FILENAME << endl;
        ofstream fout(FILENAME);
        if (groupPipe.size() != 0) {
            for (auto const& pipe : groupPipe) {
                if (groupPipe[pipe.first].km_mark != "") {
                    groupPipe[pipe.first].savePipe(fout);
                } 
            }           
        }
        if (groupCS.size() != 0) {
            for (auto const& CS : groupCS) {
                if (groupCS[CS.first].name != "") {
                    groupCS[CS.first].saveCS(fout);
                }           
            }
        }
        fout.close();
    }
}

//----------------------ВЫВОД ТРУЬЫ/КС НА КОНСОЛЬ---------------------------//
void printAllObj(map<int, pipe> groupPipe, map<int, comprSt> groupCS) {

    if (groupPipe.size() == 0) cout << "Input or load pipe to print" << endl;
    for (auto& [key, p]: groupPipe) {
        cout << "PIPE information" << endl;
        p.printPipe();
    }
    if (groupCS.size() == 0) cout << "Input or load CS to print" << endl;
    for (auto& [key, cs]: groupCS) {
        cout << "\nCS information" << endl;
        cs.printCS();
    }
}

//---------------------УДАЛЕНИЕ ТРУБЫ/КС-----------------------//
void deletePipe(map<int, pipe> &groupPipe) {
    int index = SelectPipe(groupPipe);
    groupPipe.erase(index);
}

void deleteCS(map<int, comprSt> &groupCS) {
    int index = SelectCS(groupCS);
    groupCS.erase(index);
}

//-----------------ПАКЕТНОЕ РЕДАКТИРОВАНИЕ ТРУБ/КС
void editPipeByName(map<int, pipe>& groupPipe) {

    string nameToSearch;
    cout << "Enter name to search for pipes: ";
    cin >> ws;
    getline(cin, nameToSearch);
    cerr << nameToSearch << endl;
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
    cerr << nameToSearch << endl;
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

//void creatingMatrix(map<int, comprSt>& groupCS, vector <vector <vector<int>> &matrix) {
//    //vector <vector <int>> matrix;
//    int lastKey = groupCS.rbegin()->first;
//    for (int i = 0; i < lastKey; i++) {
//        for (int j; j < lastKey; j++) {
//            matrix[i][j] = {};
//        }
//    }
//    //return matrix;
//}

void requestForParameters(int &IDEntry,int &IDExit, int &diam) {
    cout << "Enter the CS entry ID: ";
    cin >> IDEntry;
    cout << "Enter the CS exit ID: ";
    cin >> IDExit;
    cout << "Enter diametr of pipe: ";
    cin >> diam;
}

int main()
{
    redirect_output_wrapper cerr_out(cerr);
    ofstream logfile("logging.txt");
    if (logfile)
        cerr_out.redirect(logfile);

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
            newPipe.addPipe();
            pushPipe(groupPipe, newPipe);
            break;
        }
        case 2:
        {
            comprSt newCS;
            newCS.addCS();
            pushCS(groupCS, newCS);
            break;
        }
        case 3:
        {
            printAllObj(groupPipe, groupCS);
            break;
        }
        case 4:
        {
            if (groupPipe.size() != 0) {
                
                cout << "Enter 0 to search by name or 1 to search by repair: ";
                bool field = inputT(true);
                if (field == 0) {
                    editPipeByName(groupPipe);
                }
                else {
                    editPipeByRepair(groupPipe);
                }  
            }
            else {
                cout << "Input or load pipe data to edit" << endl;
            }
            break;
        }
        case 5:
        {
            if (groupCS.size() != 0){
                cout << "Enter 0 to search by name or 1 to search by percent: ";
                bool field = inputT(true);
                if (field == 0) {
                    editCSByName(groupCS);
                }
                else {
                    editCSByPer(groupCS);
                }
            }
            else {
                cout << "Input or load CS data to edit" << endl;
            }
            break;
        }
        case 6:
        {
            SaveToFile(groupPipe, groupCS);
            break;
        }
        case 7:
        {
            loadFromFile(groupPipe, groupCS);
            break;
        }
        case 8:
        {
            deletePipe(groupPipe);
            break;
        }
        case 9:
        {
            deleteCS(groupCS);
            break;
        }
        case 10:
        {
            int IDEntry, IDExit, diam;
            vector <int> usedPipe;
            requestForParameters(IDEntry, IDExit, diam);
            vector <vector <vector <int>>> matrix;
            //выбрать трубу из res или создать новую
            vector <int> res = findPipeByDiam(groupPipe, diam);
            if (!res.empty()) {
                for (auto& p : res) {
                    if (!(find(res.begin(), res.end(), p) != res.end())) {
                        //подумать про то, что является нач вершиной, а что кон
                        matrix[IDEntry][IDExit].push_back(p);
                        usedPipe.push_back(p);
                        break;
                    }
                }
                //создаём трубу
            }
            else {
                //создаём трубу
            }

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

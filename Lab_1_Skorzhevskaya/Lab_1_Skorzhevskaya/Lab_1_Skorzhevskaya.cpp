#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "comprSt.h"
#include "pipe.h"
#include "graph.h"
#include "netWork.h"
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
        << "10. Graph" << endl
        << "11. Sort" << endl
        << "0. Exit" << endl
        << "Choose action: ";
}

bool checkPipeD(int diam) {
    switch (diam) {
    case 500: {
        return 1;
    }
    case 700: {
        return 1;
    }
    case 1000: {
        return 1;
    }
    case 1400: {
        return 1;
    }
    default:
        cout << "Invalid diameter\n Try again: ";
        return 0;
    }
}

int inputValue() {
    int state;
    while (1) {
        if (!(cin >> state)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Try again: ";
        }
        else if (state >= 1 || state == -1) {
            cerr << state << endl;
            return state;
        }
        else cout << "enter value more than 0: ";
    }
    cerr << state << endl;
    return state;
}

//---------------------------ЗАПРОС ВВОДА ПАРАМЕТРОВ ДЛЯ ГРАФА------------------------------//
void requestForParameters(int& IDEntry, int& IDExit, int& diam, netWork& newNetWork) {
    while (1) {
        cout << "Enter the CS entry ID or enter -1 to create a CS: ";
        IDEntry = inputValue();
        if (IDEntry == -1)
        {
            newNetWork.addCS();
            IDEntry = newNetWork.getCS()[newNetWork.getCS().rbegin()->first].getID();
        }
        cout << "Enter the CS exit ID: ";
        IDExit = inputT(1);
        if (newNetWork.getCS().contains(IDEntry) && newNetWork.getCS().contains(IDExit) && IDEntry != IDExit)
            break;
        cout << "There are no such IDs. Enter another ID\n";
    }
    cout << "Enter diametr of pipe: ";
    diam = inputT(1);
    while (1) {
        if (!checkPipeD(diam)) {
            diam = inputT(1);
        }
        else break;
    }
}

//----------------------СОЗДАНИЕ МАТРИЦЫ СМЕЖНОСТИ-------------------------//
vector<vector<int>> createMatrix(map<int, edge>& graphG, int numNodes) {
    vector<vector<int>> matrix(numNodes);
    for (auto& [key, p] : graphG) {
        matrix[p.IDExit - 1].push_back(p.IDEntry - 1);
    }
    return matrix;
}

//--------------------------ВЫБОР ТРУБЫ/КС--------------------------//
int SelectEdge(map<int, edge> graphG) {
    cout << "Enter pipe id: ";
    while (1) {
        unsigned int index = inputT(1);
        if (index >= 1 && index < graphG.size()) {
            return index;
        }
        cout << "enter correct number: ";
    }
}

int SelectPipe(netWork& newNetWork) {
    cout << "Enter pipe id: ";
    while (1) {
        unsigned int index = inputT(1);
        for (auto& [key, p] : newNetWork.getPipe()) {
            if (key == index)
                return index;
        }
        cout << "enter correct number: ";
    }
}

int SelectCS(netWork& newNetWork) {
    cout << "Enter CS id: ";
    while (1) {
        unsigned int index = inputT(1);
        for (auto& [key, cs] : newNetWork.getCS())
        {
            if (key == index)
                return index;
        }
        cout << "enter correct number: ";
    }
}

//---------------------------------СОХРАНЕНИЕ В ФАЙЛ-----------------------------//
void SaveToFile(netWork& newNetWork, map<int, edge>& graphG) {
    if (newNetWork.getPipe().size() == 0 && newNetWork.getCS().size() == 0) cout << "Input or load data to save" << endl;
    else {
        string FILENAME;
        cout << "Enter name of file to save:";
        cin >> FILENAME;
        cerr << FILENAME << endl;
        ofstream fout(FILENAME);
        newNetWork.saveToFile(fout);
        if (graphG.size() != 0) fout << "G" << endl;
        for (auto const& edge : graphG) {
            graphG[edge.first].saveEdge(fout);
            if (edge.first != graphG.rbegin()->first)
                fout << endl;
        }
        fout.close();
    }
}

//------------------------------ЗАГРУЗКА ИЗ ФАЙЛА--------------------------------//
void loadFromFile(netWork& newNetWork, vector<int>& usedPipe, map<int, edge>& graphG) {
    string FILENAME;
    string marker;
    cout << "Enter name of file to load:";
    cin >> FILENAME;
    cerr << FILENAME << endl;
    ifstream fin(FILENAME);
    edge::maxIdG = 1;
    if (fin.is_open()) {
        newNetWork.loadFromFile(fin);
        edge newEdge;
        while (!fin.eof()) {
            newEdge.loadEdge(fin);
            graphG.insert(pair<int, edge>(edge::maxIdG, newEdge));
            edge::maxIdG++;
        }
        for (auto& [key, edge] : graphG) {
            for (auto& [ind, p] : newNetWork.getPipe()) {
                bool findEdge = (find(usedPipe.begin(), usedPipe.end(), ind) != usedPipe.end());
                if ((edge.diam == p.diam) && !findEdge) {
                    edge.pipeID = ind;
                    usedPipe.push_back(ind);
                    break;
                }
            }
        }
    }
    fin.close();
}

//--------------ПОИСК ТРУБ/КС ПО ЗАДАННОМУ ФИЛЬТРУ-------------------//
vector<int> findPipebyName(netWork& newNetWork, string name) {
    vector <int> res;
    for (int i = 0; i < newNetWork.getPipe().size(); i++) {
        if (newNetWork.getPipe()[i].km_mark == name)
            res.push_back(i+1);
    }
    return res;
}
vector<int> findPipeByDiam(netWork& newNetWork, int diam) {
    vector <int> res;
    for (int i = 0; i < newNetWork.getPipe().size()+1; i++) {
        if (newNetWork.getPipe()[i].diam == diam)
            res.push_back(i);
    }
    return res;
}
vector<int> findPipebyRepair(netWork& newNetWork, bool repair) {
    vector <int> res;
    for (int i = 0; i < newNetWork.getPipe().size(); i++) {
        if (newNetWork.getPipe()[i].repair == repair)
            res.push_back(i+1);
    }
    return res;
}
vector<int> findCSbyName(netWork& newNetWork, string name) {
    vector <int> res;
    for (int i = 0; i < newNetWork.getCS().size(); i++) {
        if (newNetWork.getCS()[i].name == name)
            res.push_back(i+1);//i или i+1
    }
    return res;
}
vector<int> findCSbyPer(netWork& newNetWork, int per) {
    vector <int> res;
    for (int i = 0; i < newNetWork.getCS().size(); i++) {
        int k = round((100.0 * (newNetWork.getCS()[i].numOfWS - newNetWork.getCS()[i].WSinOperation)) / newNetWork.getCS()[i].numOfWS);
        if (k == per)
            res.push_back(i+1);
    }
    return res;
}

//-----------------ПАКЕТНОЕ РЕДАКТИРОВАНИЕ ТРУБ/КС-------------------------//
void editPipeByName(netWork& newNetWork) {

    string nameToSearch;
    cout << "Enter name to search for pipes: ";
    cin >> ws;
    getline(cin, nameToSearch);
    cerr << nameToSearch << endl;
    vector<int> res = findPipebyName(newNetWork, nameToSearch);
    if (res.size() == 0) {
        cout << "There are no pipes with this name.\n";
        return;
    }
    newNetWork.editPipe(res);
}

void editPipeByRepair(netWork& newNetWork) {
    bool state;
    cout << "Enter repair state to search for pipes: ";
    state = inputT(true);
    vector<int> res = findPipebyRepair(newNetWork, state);
    if (res.size() == 0) {
        cout << "There are no pipes with this repair state.\n";
        return;
    }
    newNetWork.editPipe(res);
}

void editCSByName(netWork& newNetWork) {
    cout << "Enter name to search for CS: ";
    string nameToSearch;
    cin >> ws;
    getline(cin, nameToSearch);
    cerr << nameToSearch << endl;
    vector<int> res = findCSbyName(newNetWork, nameToSearch);
    if (res.size() == 0) {
        cout << "There are no CS with this name.\n";
        return;
    }
    newNetWork.editCS(res);
}

void editCSByPer(netWork& newNetWork) {
    cout << "Enter persent to search for pipes: ";
    int per;
    per = inputT(1);
    vector<int> res = findCSbyPer(newNetWork, per);
    if (res.size() == 0) {
        cout << "There are no CS with this percent.\n";
        return;
    }
    newNetWork.editCS(res);
}

//
void editPipe(netWork& newNetWork) {
    if (newNetWork.getPipe().size() != 0) {

        cout << "Enter 0 to search by name or 1 to search by repair: ";
        bool field = inputT(true);
        if (field == 0) {
            editPipeByName(newNetWork);
        }
        else {
            editPipeByRepair(newNetWork);
        }
    }
    else {
        cout << "Input or load pipe data to edit" << endl;
    }
}

void editCS(netWork& newNetWork) {
    if (newNetWork.getCS().size() != 0) {
        cout << "Enter 0 to search by name or 1 to search by percent: ";
        bool field = inputT(true);
        if (field == 0) {
            editCSByName(newNetWork);
        }
        else {
            editCSByPer(newNetWork);
        }
    }
    else {
        cout << "Input or load CS data to edit" << endl;
    }
}
//---------------------ТОПОЛОГИЧЕСКАЯ СОРТИРОВКА------------------------//

bool hasCycleDFS(vector<vector<int>>& graph, int node, vector<bool>& visited, vector<bool>& recursionStack) {
    visited[node] = true;
    recursionStack[node] = true;

    for (int neighbor : graph[node]) {
        if (!visited[neighbor] && hasCycleDFS(graph, neighbor, visited, recursionStack)) {
            return true;
        }
        else if (recursionStack[neighbor]) {
            return true;
        }
    }
    recursionStack[node] = false;
    return false;
}

bool hasCycle(vector<vector<int>>& graph, int numNodes) {
    vector<bool> visited(numNodes, false);
    vector<bool> recursionStack(numNodes, false);

    for (int i = 0; i < numNodes; i++) {
        if (!visited[i] && hasCycleDFS(graph, i, visited, recursionStack)) {
            return true;
        }
    }
    return false;
}

void topologicalSort(vector<vector<int>>& graph, int node, vector<bool>& visited, vector<int>& recursionStack) {
    visited[node] = true;
    for (int neighbor : graph[node])
        if (!visited[neighbor])
            topologicalSort(graph, neighbor, visited, recursionStack);
    recursionStack.push_back(node);
}

void Sort(map<int, edge>& graphG, netWork& newNetWork, vector<int>& deletedCS) {
    vector<vector<int>>matrix = createMatrix(graphG, newNetWork.getCS().size());
    vector<int> resOfTop;
    if (hasCycle(matrix, newNetWork.getCS().size())) {
        cout << "Graph has a cicle" << endl;
    }
    else {
        cout << "Graph does not have a cicle" << endl;
        vector<bool>visited(newNetWork.getCS().size());
        for (int node = 0; node < newNetWork.getCS().size(); node++)
            if (!visited[node])
                topologicalSort(matrix, node, visited, resOfTop);

        reverse(resOfTop.begin(), resOfTop.end());
        for (int i = 0; i < deletedCS.size(); i++) {
            for (int j = 0; j < resOfTop.size(); j++) {
                if (resOfTop[j] + 1 >= deletedCS[i]) resOfTop[j]++;
            }
        }
        for (int node : resOfTop) {
            cout << node + 1 << " ";
        }
        cout << endl;
    }
}

//-----------------------------MAIN---------------------------//
int main()
{
    redirect_output_wrapper cerr_out(cerr);
    ofstream logfile("logging.txt");
    if (logfile) cerr_out.redirect(logfile);
    map<int, edge> graphG;
    vector <int> usedPipe;
    vector <int> deletedCS;
    netWork newNetWork;

    while (1)
    {
        printMenu();
        int i = inputT(9);
        switch (i)
        {
        case 1:
        {
            newNetWork.addPipe();
            break;
        }
        case 2:
        {
            newNetWork.addCS();
            break;
        }
        case 3:
        {
            newNetWork.printAllObj();
            for (auto const& edge : graphG) {
                graphG[edge.first].printEdge();
            }
            break;
        }
        case 4:
        {
            editPipe(newNetWork);
            break;
        }
        case 5:
        {
            editCS(newNetWork);
            break;
        }
        case 6:
        {
            SaveToFile(newNetWork, graphG);
            break;
        }
        case 7:
        {
            loadFromFile(newNetWork, usedPipe, graphG);
            break;
        }
        case 8:
        {
            int index = SelectPipe(newNetWork);
            for (auto& [ind, edge] : graphG) {
                if (newNetWork.getPipe()[index].diam == edge.diam && index == edge.pipeID)
                {
                    graphG.erase(ind);
                    break;
                }
            }
            newNetWork.deletePipe(index);
            break;
        }
        case 9:
        {
            vector<int> deleteEdge;
            int index = SelectCS(newNetWork);
            for (auto& [ind, edge] : graphG) {
                if (index == edge.IDEntry || index == edge.IDExit)
                {
                    deleteEdge.push_back(ind);
                }
            }
            for (int i = 0; i < deleteEdge.size(); i++) {
                graphG.erase(deleteEdge[i]);
            }
            deletedCS.push_back(index);
            newNetWork.deleteCS(index);
            break;
        }
        case 10:
        {
            int IDEntry, IDExit, diam;
            bool flag = 0;
            requestForParameters(IDEntry, IDExit, diam, newNetWork);
            while(1)
            {
                vector <int> res = findPipeByDiam(newNetWork, diam);
                for (auto& p : res) {
                    bool pipeInUse = (find(usedPipe.begin(), usedPipe.end(), p) != usedPipe.end());
                    if (!pipeInUse) {
                        edge newEdge;
                        newEdge.addEdge(IDEntry, IDExit, newNetWork.getPipe()[p]);
                        graphG.insert(pair<int, edge>(edge::maxIdG, newEdge));
                        usedPipe.push_back(p);
                        flag = 1;
                        break;
                    }
                }
                if (flag) {
                    break;
                }
                newNetWork.addPipe();
            }
            for (auto& [key, p] : graphG) {
                p.printEdge();
            }
            break;
        }
        case 11:
        {
            Sort(graphG, newNetWork, deletedCS);
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

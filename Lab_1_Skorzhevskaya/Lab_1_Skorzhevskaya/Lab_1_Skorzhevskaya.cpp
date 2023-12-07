﻿#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "comprSt.h"
#include "pipe.h"
#include "graph.h"
#include "netWork.h"
#include "utils.h"

//#include "pushElements.cpp"
//#include "pushPipeE.cpp"
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
        << "12. Save graph" << endl
        << "13. Load graph" << endl
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

//--------------------------ВЫБОР ТРУБЫ/КС--------------------------//
int SelectG(map<int, graph> graphG) {
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
        /*if (index >= 1 && index < newNetWork.getPipe().size()) {
            
        }*/
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
        /*if (index >= 1 && index < newNetWork.getCS().size()) {
            return index;
        }*/
        cout << "enter correct number: ";
    }
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
/*vector<int> findPipebyName(map<int, pipe>& groupPipe, string name) {
    vector <int> res;
    for (int i = 0; i < groupPipe.size(); i++) {
        if (groupPipe[i].km_mark == name)
            res.push_back(i);
    }
    return res;
}*/
vector<int> findPipeByDiam(netWork& newNetWork, int diam) {
    vector <int> res;
    for (int i = 0; i < newNetWork.getPipe().size()+1; i++) {
        if (newNetWork.getPipe()[i].diam == diam)
            res.push_back(i);
    }
    return res;
}
//vector<int> findPipeByDiam(map<int, pipe>& groupPipe, int diam) {
//    vector <int> res;
//    for (int i = 0; i < groupPipe.size(); i++) {
//        if (groupPipe[i].diam == diam)
//            res.push_back(i);
//    }
//    return res;
//}
vector<int> findPipebyRepair(netWork& newNetWork, bool repair) {
    vector <int> res;
    for (int i = 0; i < newNetWork.getPipe().size(); i++) {
        if (newNetWork.getPipe()[i].repair == repair)
            res.push_back(i+1);
    }
    return res;
}
/*
vector<int> findPipebyRepair(map<int, pipe>& groupPipe, bool repair) {
    vector <int> res;
    for (int i = 0; i < groupPipe.size(); i++) {
        if (groupPipe[i].repair == repair)
            res.push_back(i);
    }
    return res;
}*/
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

//------------------ДОБАВЛЕНИЕ ТРУБЫ/КС В ГРУППУ----------------------//

//void pushPipe(map<int, pipe>& groupPipe, pipe& newPipe) {
//    groupPipe.insert(pair<int, pipe>(pipe::maxPipeID, newPipe));
//    pipe::maxPipeID++;
//}
//
//void pushCS(map<int, comprSt>& groupCS, comprSt newCS) {
//    groupCS.insert(pair<int, comprSt>(comprSt::maxCSID, newCS));
//    comprSt::maxCSID++;
//}

//------------------------ЗАГРУЗКА ИЗ ФАЛА---------------------------//

//void loadFromFile(map<int, pipe>& groupPipe, map<int, comprSt>& groupCS) {
//    string FILENAME, marker;
//    cout << "Enter name of file to load:";
//    cin >> FILENAME;
//    cerr << FILENAME << endl;
//    ifstream fin(FILENAME);
//    bool flagP = 0, flagCS = 0;
//    groupPipe.erase(groupPipe.begin(), groupPipe.end());
//    groupCS.erase(groupCS.begin(), groupCS.end());
//    pipe::maxPipeID = 1;
//    comprSt::maxCSID = 1;
//    if(fin.is_open()){
//        while (!fin.eof()) {
//            fin >> marker;
//            if (marker == "PIPE") {
//                pipe newPipe;
//                newPipe.loadPipe(fin);
//                pushPipe(groupPipe, newPipe);
//                flagP = 1;
//            }
//            if (marker == "CS") {
//                comprSt newCS;
//                newCS.loadCS(fin);
//                pushCS(groupCS, newCS);
//                flagCS = 1;
//            }
//        }
//        if (!flagP) cout << "save the pipe data to a file" << endl;
//        if (!flagCS) cout << "save the CS data to a file" << endl;
//    }else {
//        cout << "Error! The file " << FILENAME <<" does not exist" << endl;
//    }
//}

//------------------------СОХРАНЕНИЕ В ФАЙЛ-----------------------------//

//void SaveToFile(map<int, pipe> groupPipe, map<int, comprSt> groupCS) {
//
//    if (groupPipe.size() == 0 && groupCS.size()==0) cout << "Input or load data to save" << endl;
//    else {
//        string FILENAME;
//        cout << "Enter name of file to save:";
//        cin >> FILENAME;
//        cerr << FILENAME << endl;
//        ofstream fout(FILENAME);
//        if (groupPipe.size() != 0) {
//            for (auto const& pipe : groupPipe) {
//                if (groupPipe[pipe.first].km_mark != "") {
//                    groupPipe[pipe.first].savePipe(fout);
//                } 
//            }           
//        }
//        if (groupCS.size() != 0) {
//            for (auto const& CS : groupCS) {
//                if (groupCS[CS.first].name != "") {
//                    groupCS[CS.first].saveCS(fout);
//                }           
//            }
//        }
//        fout.close();
//    }
//}

//----------------------ВЫВОД ТРУЬЫ/КС НА КОНСОЛЬ---------------------------//

//void printAllObj(map<int, pipe> groupPipe, map<int, comprSt> groupCS) {
//
//    if (groupPipe.size() == 0) cout << "Input or load pipe to print" << endl;
//    for (auto& [key, p]: groupPipe) {
//        cout << "\nPIPE information" << endl;
//        p.printPipe();
//    }
//    if (groupCS.size() == 0) cout << "Input or load CS to print" << endl;
//    for (auto& [key, cs]: groupCS) {
//        cout << "\nCS information" << endl;
//        cs.printCS();
//    }
//}

//-----------------------------УДАЛЕНИЕ ТРУБЫ/КС---------------------------//

//void deletePipe(map<int, pipe> &groupPipe) {
//    int index = SelectPipe(groupPipe);
//    groupPipe.erase(index);
//}
//
//void deleteCS(map<int, comprSt> &groupCS) {
//    int index = SelectCS(groupCS);
//    groupCS.erase(index);
//}

//-----------------ПАКЕТНОЕ РЕДАКТИРОВАНИЕ ТРУБ/КС-------------------------//
void editPipeByName(netWork& newNetWork) {

    string nameToSearch;
    cout << "Enter name to search for pipes: ";
    cin >> ws;
    getline(cin, nameToSearch);
    cerr << nameToSearch << endl;
    //map<int, pipe> groupPipe = newNetWork.getPipe();
    vector<int> res = findPipebyName(newNetWork, nameToSearch);
    if (res.size() == 0) {
        cout << "There are no pipes with this name.\n";
        return;
    }
    /*for (int i = 0; i < res.size(); i++) {
        newNetWork.getPipe()[res[i]].editPipe();
    }*/
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
    }/*
    for (int i = 0; i < res.size(); i++) {
        groupPipe[res[i]].editPipe();
    }*/
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
    /*for (int i = 0; i < res.size(); i++) {
        newNetWork.getCS()[res[i]].editCS();
    }*/
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
    /*for (int i = 0; i < res.size(); i++) {
        groupCS[res[i]].editCS();
    }*/
}

//void checkNumPipe(map<int, comprSt>& groupCS, int& IDEntry, int& IDExit) {
//    if (groupCS[IDEntry])
//}

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

// Функция для инициализации и вызова функции проверки наличия цикла
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

vector<vector<int>> createMatrix(map<int, graph> graphG, int numNodes) {
    vector<vector<int>> matrix(numNodes);
    for (auto& [key, p] : graphG) {
        matrix[p.IDExit-1].push_back(p.IDEntry-1);
    }
    return matrix;
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
void requestForParameters(int &IDEntry,int &IDExit, int &diam, netWork& newNetWork) {
    while (1) {
        cout << "Enter the CS entry ID or enter -1 to create a CS: ";
        IDEntry = inputValue();
        if (IDEntry == -1)
        {
            /*comprSt newCS;
            newCS.addCS();
            pushCS(groupCS, newCS);*/
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

//map<int, int> degreeOfEntry(vector<vector<int>> matrix, int numNodes) {
//    map<int, int> degreesOfNodes;
//    for (int node = 0; node < numNodes; node++)
//    {
//        //if (degreesOfNodes[node]) {
//        degreesOfNodes[node] = 0;
//    }
//    for (int node = 0; node < numNodes; node++)
//    {
//        for (int neighbor : matrix[node]) {
//            bool f = !degreesOfNodes[neighbor];
//            degreesOfNodes[neighbor]++;
//            
//        }
//    }
//    return degreesOfNodes;
//}
//map<int, int> degreeOfOutcome(vector<vector<int>> matrix, int numNodes) {
//    map<int, int> degreesOfNodes;
//    for (int node = 0; node < numNodes; node++)
//    {
//        degreesOfNodes[node] = matrix[node].size();
//    }
//    return degreesOfNodes;
//}

//vector<int> topologicalSorting(map<int, int> entryDegeeOfNodes, map<int, int> outDegeeOfNodes, vector<vector<int>> matrix, int numNodes) {
//    vector <int> res;
//    //vector <int> zeroDegree;
//    vector <int> currentNodes;
//    while (res.size() != numNodes)
//    {
//        for (int i = 0; i < entryDegeeOfNodes.size(); i++) {
//            if (entryDegeeOfNodes[i] == 0 && outDegeeOfNodes[i] == 0) {
//                //zeroDegree.push_back(i);
//                continue;
//            }
//            if (entryDegeeOfNodes[i] == 0) {
//                currentNodes.push_back(i);
//            }
//        }
//        for (int i = 0; i < currentNodes.size(); i++) {
//            for (int neighbor : matrix[i]) {
//                entryDegeeOfNodes[neighbor]--;
//            }
//            //entryDegeeOfNodes[currentNodes[i]]--;
//            res.push_back(currentNodes[i]);
//        }
//        /*for (int i = 0; i < zeroDegree.size(); i++) {
//            res.push_back(zeroDegree[i]);
//        }*/
//
//    }
//    return res;
//}

void dfs(vector<vector<int>>& graph, int node, vector<bool>& visited, vector<int>& recursionStack) {
    visited[node] = true;
    for (int neighbor : graph[node])
        if (!visited[neighbor])
            dfs(graph, neighbor, visited, recursionStack);
    recursionStack.push_back(node);
}

//-----------------------------MAIN---------------------------//
int main()
{
    string FILENAME;
    redirect_output_wrapper cerr_out(cerr);
    ofstream logfile("logging.txt");
    if (logfile)
        cerr_out.redirect(logfile);

    /*map<int, comprSt> groupCS;
    map<int, pipe> groupPipe;*/
    map<int, graph> graphG;
    //map<int, bool> nodes;//переделать на вектор
    //vector <bool> nodes;
    vector <int> usedPipe;
    netWork newNetWork;

    while (1)
    {
        printMenu();
        int i = inputT(9);
        switch (i)
        {
        case 1:
        {
            /*pipe newPipe;
            newPipe.addPipe();
            pushPipe(groupPipe, newPipe);*/
            newNetWork.addPipe();
            break;
        }
        case 2:
        {
            /*comprSt newCS;
            newCS.addCS();
            pushCS(groupCS, newCS);*/
            newNetWork.addCS();
            break;
        }
        case 3:
        {
            //printAllObj(groupPipe, groupCS);
            newNetWork.printAllObj();
            for (auto const& edge : graphG) {
                graphG[edge.first].printG();
            }

            break;
        }
        case 4:
        {
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
            break;
        }
        case 5:
        {
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
            break;
        }
        case 6:
        {
            //SaveToFile(groupPipe, groupCS);
            if (newNetWork.getPipe().size() == 0 && newNetWork.getCS().size() == 0) cout << "Input or load data to save" << endl;
            else {
                cout << "Enter name of file to save:";
                cin >> FILENAME;
                cerr << FILENAME << endl;
                ofstream fout(FILENAME);
                newNetWork.saveToFile(fout);
                if (graphG.size() != 0) fout << "G" << endl;
                for (auto const& edge : graphG) {
                    graphG[edge.first].saveGraph(fout);
                    if (edge.first != graphG.rbegin()->first)
                        fout << endl;
                }
                fout.close();
            }
            break;
        }
        case 7:
        {
            string marker;
            cout << "Enter name of file to load:";
            cin >> FILENAME;
            cerr << FILENAME << endl;
            ifstream fin(FILENAME);
            graph::maxIdG = 1;
            if (fin.is_open()) {
                newNetWork.loadFromFile(fin);
                graph newEdge;
                while (!fin.eof()) {
                    newEdge.loadGraph(fin);
                    graphG.insert(pair<int, graph>(graph::maxIdG, newEdge));
                    graph::maxIdG++;
                }
                for (auto& [key, edge] : graphG) {
                    for (auto& [ind, p]: newNetWork.getPipe()) {
                        bool findEdge = (find(usedPipe.begin(), usedPipe.end(), ind) != usedPipe.end());
                        if ((edge.diam == p.diam) && !findEdge) {
                            edge.pipeID = ind;
                            usedPipe.push_back(ind);
                            break;
                        }
                    }
                }
                /*//usedPipe.push_back(p);
                nodes[newEdge.IDEntry] = 1;
                nodes[newEdge.IDExit] = 1;*/
                //netWork::loadFromFile(fin);
                //while (!fin.eof()) {
                //    graph newEdge;
                //    newEdge.loadGraph(fin);
                //    graphG.insert(pair<int, graph>(graph::maxIdG, newEdge));
                //    //usedPipe.push_back(p);
                //    nodes[newEdge.IDEntry] = 1;
                //    nodes[newEdge.IDExit] = 1;
                //    graph::maxIdG++;
                //}
            }
            fin.close();
            //loadFromFile(groupPipe, groupCS);
            break;
        }
        case 8:
        {
            //deletePipe(groupPipe);
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
                //newNetWork.getCS()[index].getID()
                if (index == edge.IDEntry || index == edge.IDExit)
                {
                    deleteEdge.push_back(ind);
                    /*graphG.erase(ind);
                    break;*/
                }
            }
            for (int i = 0; i < deleteEdge.size(); i++) {
                graphG.erase(deleteEdge[i]);
            }
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
                    bool findEdge = (find(usedPipe.begin(), usedPipe.end(), p) != usedPipe.end());
                     
                    if (!(find(usedPipe.begin(), usedPipe.end(), p) != usedPipe.end())) {
                        graph newEdge;
                        newEdge.addEdge(IDEntry, IDExit, newNetWork.getPipe()[p]);
                        graphG.insert(pair<int, graph>(graph::maxIdG, newEdge));
                        usedPipe.push_back(p);
                        //nodes.insert(pair<int, bool>(IDEntry, 1));
                        //nodes.insert(pair<int, bool>(IDExit, 1));
                        flag = 1;
                        break;
                    }
                }
                if (flag) {
                    break;
                }
                /*pipe newPipe;
                newPipe.addPipe();
                pushPipe(groupPipe, newPipe);*/
                newNetWork.addPipe();
            }
            for (auto& [key, p] : graphG) {
                p.printG();
            }
            break;
        }
        case 11:
        {
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
                        dfs(matrix, node, visited, resOfTop);
                reverse(resOfTop.begin(), resOfTop.end());
                for (int node : resOfTop) {
                    cout << node + 1 << " ";
                }
                cout << endl;
                //int flagE = 0, flagO = 0;
                //map<int, int> entryDegreesOfNodes = degeeOfEntry(matrix, groupCS.size());
                //map<int, int> outDegreesOfNodes = degeeOfOutcome(matrix, groupCS.size());
                //for (int i = 0; i < groupCS.size(); i++) {
                //    if (entryDegreesOfNodes[i] == 0)
                //        flagE = 1;
                //    if (outDegreesOfNodes[i] == 0)
                //        flagO = 1;
                //}
                //if (flagE && flagO) {
                //    //топологическая сортировка
                //    resOfTop = topologicalSorting(entryDegreesOfNodes, outDegreesOfNodes, matrix, nodes.size());
                //}
            }
            
            break;
        }
        //case 12:
        //{
        //    ofstream fout("GRAPH.TXT");
        //    for (auto const& edge : graphG) {
        //        graphG[edge.first].saveGraph(fout);
        //    }
        //    break;
        //}
        //case 13:
        //{
        //    graph::maxIdG = 1;
        //    ifstream fin("GRAPH.TXT");
        //    if(fin.is_open()) {
        //        while (!fin.eof()) {
        //            graph newEdge;
        //            newEdge.loadGraph(fin);
        //            graphG.insert(pair<int, graph>(graph::maxIdG, newEdge));
        //            //usedPipe.push_back(p);
        //            nodes[newEdge.IDEntry] = 1;
        //            nodes[newEdge.IDExit] = 1;
        //            graph::maxIdG++;
        //        }
        //    }
        //    break;
        //}
        //case 14:
        //{
        //    int index = SelectG(graphG);
        //    graphG.erase(index);
        //    break;
        //}
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

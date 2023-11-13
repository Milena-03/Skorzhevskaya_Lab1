#include <iostream>
#include <string>

using namespace std;

bool checkNumWSinOperation(int checkValue, int numWS) {
    if ((checkValue > numWS) || (checkValue < 0)) return 1;
    else return 0;
}
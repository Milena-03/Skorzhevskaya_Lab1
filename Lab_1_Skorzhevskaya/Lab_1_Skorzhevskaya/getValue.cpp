#include <iostream>
#include <string>

using namespace std;

template <typename T>

T inputT(T value) {

    T state;
    while (1) {
        if (!(cin >> state)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Try again: ";
        }
        else if (state >= 0) {
            return state;
        }
        else cout << "enter value more than 0: ";
    }
    return state;
}
#pragma once
#include <iostream>
#include <string>
using namespace std;
class redirect_output_wrapper
{
    ostream& stream;
    streambuf* const old_buf;
public:
    redirect_output_wrapper(ostream& src)
        :old_buf(src.rdbuf()), stream(src)
    {
    }
    ~redirect_output_wrapper() {
        stream.rdbuf(old_buf);
    }
    void redirect(ostream& dest) {
        stream.rdbuf(dest.rdbuf());
    }
};

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
            cerr << state << endl;
            return state;
        }
        else cout << "enter value more than 0: ";
    }
    cerr << state << endl;
    return state;
}
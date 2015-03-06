/*
ID: guofeng2
TASK: test
LANG: C++11
*/

#include <fstream>
#include <iostream>
#define _PRINT_(a)  cerr<<#a<<"="<<a<<endl;

using namespace std;

class Calculator{
    ifstream in;
    ofstream out;

    int a, b;
public:

    Calculator(const string & name):in(name+".in"), out(name+".out")
    { in >> a >> b; }

    void run() { 
        out<<(a+b)<<endl; 
        out<<string("1234").substr(2, 5)<<endl;
    }
};

int main() { Calculator("test").run(); }

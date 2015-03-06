/*
ID: guofeng2
TASK: concom
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#define _PRINT_(a)  cerr<<#a<<"="<<a<<endl;

using namespace std;

struct Link {
    int first, second, percent; 
    Link(int a, int b, int c):first(a), second(b), percent(c) {}
};

class Calculator{
    ifstream in;
    ofstream out;

    int N;
    vector<Link>    links;
public:
    Calculator(const string & name):in(name+".in"), out(name+".out")
    { 
        in >> N;
        for(int i=0; i<N; ++i)
        {
            int a, b, c;
            in>>a>>b>>c;
            links.push_back(Link(a, b, c));
        }
    }

    void run() {
    }
};

int main() { Calculator("concom").run(); }

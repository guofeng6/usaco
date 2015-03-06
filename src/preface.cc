/*
ID: guofeng2
TASK: preface
LANG: C++11
*/

#include <fstream>
#include <map>
#include <iostream>
#define _PRINT_(a)  out<<#a<<"="<<a<<endl;

using namespace std;

/* symbols for roman numbers
   I   1     L   50    M  1000
   V   5     C  100
   X  10     D  500
 */

class Calculator{
    ifstream in;
    ofstream out;

    int N;

    string convert(int n, const char * p) 
    {
        string x    = "";
        switch(n%10)
        {
            case 0:     return x;
            case 1:     return x + p[0];
            case 2:     return x + p[0] + p[0];
            case 3:     return x + p[0] + p[0] + p[0];;
            case 4:     return x + p[0] + p[1];
            case 5:     return x + p[1];
            case 6:     return x + p[1] + p[0];
            case 7:     return x + p[1] + p[0] + p[0];
            case 8:     return x + p[1] + p[0] + p[0] + p[0];
            default:    return x + p[0] + p[2];
        }
    }

    string roman_number(int n) 
    {
        string s;
        s += convert(n / 1000,  "M**");
        s += convert(n / 100,   "CDM");
        s += convert(n / 10,    "XLC"); 
        s += convert(n,         "IVX"); 
        return s;
    }
public:

    Calculator(const string & name):in(name+".in"), out(name+".out")
    { in >> N; }

    void run() 
    {
        map<char, int> m;
        string sym = "IVXLCDM";
        for(auto c:sym)     m[c]   = 0;

        for(int i=1; i<=N; ++i)
        {
            string s = roman_number(i);
            for(auto c: s) ++m[c];
        }

        for(auto c: sym)
            if (m[c]) out<<c<<' '<<m[c]<<endl;
    }
};

int main() { Calculator("preface").run(); }

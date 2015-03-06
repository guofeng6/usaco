/*
ID: guofeng2
TASK: palsquare
LANG: C++11
*/

#include <fstream>

using namespace std;

const char * num_map  = "0123456789ABCDEFGHIJKLMNOPQ";

string get_string(int n, int B)
{
    string s;
    while(n)
    {
        s   += num_map[n%B];
        n   =  n/B; 
    }
    return s;
}

string reverse_string(const string & s)
{
    string r;
    for(int i=0; i<s.size(); ++i)
        r += s[s.size()-1-i];
    return r;
}

class Calculator{
    ifstream in;
    ofstream out;

    int B;
public:

    Calculator(const string & name):in(name+".in"),out(name+".out")
    { in >> B; }

    void run() {
        for (int i=1; i<=300; ++i)
        {
            auto s = get_string(i*i, B);
            if(reverse_string(s)==s)
                out<<reverse_string(get_string(i, B))<<' '<<s<<endl;
        }
    }
};

int main() { Calculator("palsquare").run(); }

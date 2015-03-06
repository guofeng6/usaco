/*
ID: guofeng2
TASK: ride
LANG: C++
*/

#include <fstream>
#include <iostream>

using namespace std;

int get_code(const string & s)
{
    int   n = 1;
    for(int i=0; i<s.size(); ++i)
        n   = (n*(s[i]-'A' + 1)) % 47;
    return n;
}

int main()
{
    ifstream in("ride.in");
    ofstream out("ride.out");

    string a, b; in>>a>>b;

    if(get_code(a) == get_code(b))
        out<<"GO"<<endl;
    else
        out<<"STAY"<<endl;
}

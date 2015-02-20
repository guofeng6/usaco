/*
ID: guofeng2
TASK: ride
LANG: C++
*/

#include <fstream>
#include <iostream>

using namespace std;

int get_code(istream & in)
{
    char  c;
    int   n = 1;
    while(in)
    {
        c = in.get();
        if (c=='\n' || c== EOF)
            break;
        n = (n*(c-'A' + 1)) % 47;
    }

    return n;
}

int main()
{
    ifstream in("ride.in");
    ofstream out("ride.out");

    int a   = get_code(in); 
    int b   = get_code(in); 

    if (a==b)
        out<<"GO"<<endl;
    else
        out<<"STAY"<<endl;

    return 0;
}

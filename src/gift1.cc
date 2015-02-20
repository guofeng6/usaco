/*
ID: guofeng2
TASK: gift1
LANG: C++
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <stdlib.h>

using namespace std;

string get_line(istream & in)
{
    string s;
    while(in)
    {
        char c = in.get();
        if (c=='\n' || c== EOF)
            break;
        s += c;
    }

    return s;
}

int main()
{
    ifstream in("gift1.in");
    ofstream out("gift1.out");

    int np  = atoi(get_line(in).c_str());
    map<string, int>  m_player;
    vector<string>    v_player;


    for(int i=0; i<np; ++i)
    {
        string nm = get_line(in);
        m_player.insert(make_pair(nm, 0));
        v_player.push_back(nm);
    }

    while(1)
    {
        string nm = get_line(in);
        istringstream s(get_line(in));
        if(!in) break;
        int amt, ng;
        s>>amt>>ng;
        if(ng<=0) continue;

        int give_amt  = amt / ng;

        m_player[nm]   -= give_amt * ng;

        for (int i=0; i<ng; ++i)
        {
            string nmr = get_line(in);
            m_player[nmr]  += give_amt; 
        }
    }

    for(int i=0;i< np; ++i)
    {
        string nm = v_player[i];
        out<<nm<<' '<<m_player[nm]<<endl;
    }

    return 0;
}

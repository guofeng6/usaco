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

int main()
{
    ifstream in("gift1.in");
    ofstream out("gift1.out");

    int np;     in>>np;
    map<string, int>  m_player;
    vector<string>    v_player;

    for(int i=0; i<np; ++i)
    {
        string nm;  in>>nm;
        m_player.insert(make_pair(nm, 0));
        v_player.push_back(nm);
    }

    while(in)
    {
        string nm;      in>>nm; 
        int amt, ng;    in>>amt>>ng;
        if(ng==0)   break;

        int give_amt    =   amt / ng;
        m_player[nm]    -=  give_amt * ng;

        for (int i=0; i<ng; ++i)
        {
            string nmr;     in>>nmr;
            m_player[nmr]   += give_amt; 
        }
    }

    for(int i=0; i<np; ++i)
    {
        string nm   = v_player[i];
        out<<nm<<' '<<m_player[nm]<<endl;
    }
}

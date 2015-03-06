/*
ID: guofeng2
TASK: combo
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <set>
#define _PRINT_(a)  out<<#a<<"="<<a<<endl;

using namespace std;

struct Combo{
    static int N;
    int id;

    Combo(){}

    Combo create(int a, int b, int c)
    {
        Combo x;
        x.id = make_id(a, b, c);
        return x;
    }

    int fix(int a) const { return ((a-1 + N) % N); }

    int make_id(int a, int b, int c) const {
        return fix(a) * N * N + fix(b) * N + fix(c); 
    }

    void get_triplet(int & a, int & b, int & c) const
    {
        int x   = id;
        c       = x % N + 1;    x /= N;
        b       = x % N + 1;    x /= N;
        a       = x + 1; 
    }

    bool operator<(const Combo & x) const { return id < x.id; }

    void get_openable(set<Combo> & all) 
    {
        int a, b, c;
        get_triplet(a, b, c);
        for(int i=-2; i<=2; ++i)
        {
            for(int j=-2; j<=2; ++j)
            {
                for(int k=-2; k<=2; ++k)
                    all.insert(create(a+i, b+j, c+k));
            }
        }
    }
};

istream & operator>>(istream & in, Combo & x) 
{ 
    int a, b, c;    in>>a>>b>>c; 
    x.id    = x.make_id(a, b, c);
    return in;
}

ostream & operator<<(ostream & o, const Combo & x) 
{ 
    int a, b, c;
    x.get_triplet(a, b, c);
    return o<<'('<<a<<','<<b<<','<<c<<')'; 
}

int Combo::N;

int main()
{
    ifstream in("combo.in");
    ofstream out("combo.out");

    in>>Combo::N;

    Combo farmer_combo; in>>farmer_combo;
    Combo master_combo; in>>master_combo;

    set<Combo> openable;    
    farmer_combo.get_openable(openable);
    master_combo.get_openable(openable);

    out<<openable.size()<<endl;
}

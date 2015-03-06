/*
ID: guofeng2
TASK: skidesign
LANG: C++11
*/

#include <fstream>
#include <vector>
#define _PRINT_(a)  out<<#a<<"="<<a<<endl;

using namespace std;

struct Hill
{
    int h_old;
    int h_new;

    Hill(int h):h_old(h), h_new(h){}

    int cost()   const { auto d = change(); return d*d; }
    int change() const { return h_new-h_old; }

    int fix(int low)
    {
        if (h_old < low) 
            h_new = low;
        else if (h_old > low + 17) 
            h_new = low + 17;
        else
            h_new = h_old;

        return cost();
    }
};

ostream & operator<<(ostream & o, const Hill & a)
{
    return o<<'('<<a.h_old<<' '<<a.h_new<<')';
}

int main()
{
    ifstream in("skidesign.in");
    ofstream out("skidesign.out");
    int N; in>>N;

    vector<Hill>    hills;

    int min_h=100;
    int max_h=0;

    for(int i=0; i<N; ++i)
    {
        int h;  in>>h;

        hills.push_back(Hill(h));

        if (h < min_h)  min_h = h;
        if (h > max_h)  max_h = h;
    }

    int min_cost    = 100 * 100 * N;

    if (max_h - min_h <= 17)
        min_cost    = 0;

    for(int low = min_h; low <= max_h - 17; ++low)
    {
        int cost    = 0;

        for(int i=0; i<N; ++i)
            cost += hills[i].fix(low);

        if (cost < min_cost ) min_cost = cost;
    }

    out<<min_cost<<endl;
}

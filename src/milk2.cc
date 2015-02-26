/*
ID: guofeng2
TASK: milk2
LANG: C++
*/

#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Bracket{
    int first;
    int second;

    Bracket(int a, int b) : first(a), second(b) {}
    Bracket(const Bracket & a) : first(a.first), second(a.second) {}
    Bracket & operator=(const Bracket & b) { first=b.first; second=b.second; }

    bool operator<(const Bracket & a) const { return first < a.first; }
};

ostream & operator<<(ostream & o, const Bracket & b) 
{ 
    return o<<"("<<b.first<<","<<b.second<<")"<<endl; 
}

typedef vector<Bracket> Vec;

int main()
{
    vector<Bracket> all;
    ifstream in ("milk2.in");
    ofstream out("milk2.out");

    int N; in>>N;

    for(int i=0; i<N; ++i)
    {
        int a, b;
        in>>a>>b;
        all.push_back(Bracket(a, b));
    }

    sort(all.begin(), all.end());

    int max_gap     = 0;
    int max_non_gap = 0;

    if (!all.empty())
    {
        Bracket current = all.front();
        Vec::iterator p = all.begin();
       
        while(p!=all.end())
        {
            p++;

            if (p==all.end())
            {
                int non_gap = current.second - current.first;
                if ( non_gap > max_non_gap ) max_non_gap = non_gap;
            }
            else if (p->second <= current.second) 
                //*p is contained in current, do nothing
                continue;
            else if (p->first<=current.second) 
                //*p overlaps with current, expand current
            {
                current.second    = p->second;
                continue;
            }
            else
            {
                int non_gap = current.second - current.first;
                if ( non_gap > max_non_gap ) max_non_gap = non_gap;

                int gap     = p->first - current.second;
                if (gap > max_gap) max_gap = gap;

                current = *p;
            }
        }
    }

    out<<max_non_gap<<' '<<max_gap<<endl;

    return 0;
}

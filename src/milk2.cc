/*
ID: guofeng2
TASK: milk2
LANG: C++11
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
    Bracket & operator=(const Bracket & b) { first=b.first; second=b.second; return *this;}

    bool operator<(const Bracket & a) const { return first < a.first; }
};

ostream & operator<<(ostream & o, const Bracket & b) 
{ 
    return o<<"("<<b.first<<","<<b.second<<")"<<endl; 
}

struct max_num{
    int num;
    max_num():num(0){}
    void update(int n) { if (n > num) num    = n; } 
};

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

    max_num max_gap, max_non_gap;

    if (!all.empty())
    {
        Bracket current = all.front();
        auto p = all.begin();
       
        while(p!=all.end())
        {
            ++p;

            if (p==all.end())
                max_non_gap.update(current.second - current.first);
            else if (p->second <= current.second);
                //*p is contained in current, do nothing
            else if (p->first  <= current.second)   
                //*p overlaps with current, expand current
                current.second    = p->second;
            else
            {
                max_non_gap.update(current.second - current.first);
                max_gap.update(p->first - current.second);

                current = *p;
            }
        }
    }

    out<<max_non_gap.num<<' '<<max_gap.num<<endl;
}


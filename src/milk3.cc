/*
ID: guofeng2
TASK: milk3
LANG: C++11
*/

#include <fstream>
#include <set>
#include <iostream>
#define _PRINT_(a)  out<<#a<<"="<<a<<endl;

using namespace std;

struct Bucket
{
    int     capacity;
    int     used_capacity;

    void    init(int c, int u)          { capacity=c; used_capacity=u; }
    bool    is_empty()          const   { return used_capacity == 0; }
    int     usable_capacity ()  const   { return capacity - used_capacity; }

    int     pour_into(Bucket & b)
    {
        int amount  = b.usable_capacity();
        if( amount  > used_capacity)
            amount  = used_capacity;
        used_capacity   -= amount;
        b.used_capacity += amount;
        return amount;
    }
};

class Bucket3{
    Bucket all[3];

    set<int>    visited_ids;
    set<int>    valid_set;

    int get_id() { return all[0].used_capacity + all[1].used_capacity * 21; }
    //the state is uniquely identified by the amount in the first two
    //buckets.

public:
    Bucket3(int a, int b, int c)
    {
        all[0].init(a, 0);
        all[1].init(b, 0);
        all[2].init(c, c);
    }

    void print()
    {
        cerr<<"(";
        for(int i=0; i<3; ++i)
            cerr<<all[i].used_capacity<<' ';
        cerr<<")  "<<endl;
    }

    //recursively pour around.
    //this is guaranteed to finish since the all possible states are
    //finite, and we are only visiting each state once.
    void pour_around()
    {
        if(all[0].is_empty()) 
            valid_set.insert(all[2].used_capacity);

        int id  = get_id();
        if(visited_ids.find(id)!=visited_ids.end()) 
            return;
        else 
            visited_ids.insert(id);

        //loop through all possibilities in one pouring operation.
        for(int i=0; i<3; ++i)
            for(int j=0; j<3; ++j)
                if (i!=j)
                {
                    int amount              = all[i].pour_into(all[j]);
                    pour_around();
                    all[i].used_capacity    += amount;
                    all[j].used_capacity    -= amount;
                }
    }

    void print_valid_set(ostream & out)
    {
        int n = valid_set.size()-1;
        for(auto it=valid_set.begin(); n>0; ++it, --n)
            out<<*it<<' ';
        out<<*valid_set.rbegin()<<endl;
    }
};

int main()
{
    ifstream in("milk3.in");
    ofstream out("milk3.out");
    int a, b, c;    in>>a>>b>>c;

    Bucket3 b3(a, b, c);
    b3.pour_around();
    b3.print_valid_set(out);
}

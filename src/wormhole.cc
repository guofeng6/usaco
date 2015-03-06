/*
ID: guofeng2
TASK: wormhole
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#define _PRINT_(a)  cerr<<#a<<"="<<a<<endl;

using namespace std;

class World;

struct Hole {
    int x, y;
    Hole    * partner;
    Hole    * next;         //neighbor to the right of this hole.

    Hole(int a, int b): x(a), y(b), partner(0), next(0) {}

    void connect(Hole * p)      { p->partner       = this;   partner = p; }
    void disconnect()           { partner->partner = 0;      partner = 0; }
    bool is_connected() const   { return partner; }

    //make sure that the holes on the same row are next to each other when sorted.
    bool operator<(const Hole & a) const { return y<a.y || (y==a.y && x<a.x); }
};

ostream & operator<<(ostream & o, const Hole & h) 
{ 
    return o<<'('<<h.x<<','<<h.y<<')'; 
}

template <class T>
struct ptr_less{ 
    bool operator()(const T * f1, const T * f2) const { return *f1<*f2;}
};

class World {
    typedef vector<Hole *>  HoleVec;
    int N, N2;

    HoleVec         hole_vec;
    int             dead_count;
public:
    World(int n): N(n), N2(n/2) {}

    void add_hole(int x, int y) { hole_vec.push_back(new Hole(x, y)); }

    void setup_next()
    {
        sort(hole_vec.begin(), hole_vec.end(), ptr_less<Hole>());

        for(int i=0; i<hole_vec.size()-1; ++i)
        {
            auto p     = hole_vec[i];
            auto next  = hole_vec[i+1];
            if (p->y==next->y)
                p->next = next;
        }
    }
   
    bool is_live_entry(Hole * p) const
    {
        //Among N2+1 pairs there must be two that are the same. 
        //If we go over N2+1 pairs without seeing the exit we must be in a 
        //dead loop.
        for(int i=0; i<N2+1; ++i)
        {
            p = p->partner->next;
            if (!p)  //no more holes to the right of this hole, so we are out.
                return true;
        }
        return false;
    }

    int find_all_dead_pairings()
    {
        dead_count = 0;
        recursive_visit();
        return dead_count;
    }

    int get_first_free()
    {
        for(int i=0; i<N; ++i)
            if (!hole_vec[i]->is_connected())
                return i;
        return -1;
    }

    int find_dead_loop() const 
    {
        int dead = 0;
        for(int i=0; i<N; ++i)
        {
            if(!is_live_entry(hole_vec[i]))
            {
                dead = 1;
                break;
            }
        }
        return dead;
    }

    void recursive_visit()
    {
        auto p0 = get_first_free();
        if(p0 < 0) 
            dead_count += find_dead_loop();
        else 
        {
            for(int i=p0+1; i<N; ++i)
            {
                if (!hole_vec[i]->is_connected())
                {
                    hole_vec[p0]->connect(hole_vec[i]);
                    recursive_visit();
                    hole_vec[p0]->disconnect();
                }
            }
        }
    }
};

int main()
{
    ifstream in("wormhole.in");
    ofstream out("wormhole.out");

    int N;      in>>N;

    World w(N);

    for(int i=0; i<N; ++i)
    {
        int x, y; in>>x>>y;
        w.add_hole(x, y);
    }

    w.setup_next();

    auto n = w.find_all_dead_pairings();

    out<<n<<endl;
}


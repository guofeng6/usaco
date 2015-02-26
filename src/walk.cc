// solution to 2015 amc 10b problem 24.
#include <fstream>
#include <vector>
#include <algorithm>
#include "assert.h"

using namespace std;

struct Point {
    int x, y;
    Point(int a, int b):x(a), y(b) {}
    Point operator+(const Point & p)  const { return Point(x+p.x,  y+p.y); }
    Point operator-(const Point & p)  const { return Point(x-p.x,  y-p.y); }
    bool  operator==(const Point & p) const { return x==p.x && y == p.y; }
    Point & operator=(const Point & p){ x=p.x; y = p.y; return *this;}
};

ostream & operator<<(ostream & o, const Point & p) 
{ return o<<p.x<<' '<<p.y; } 

Point get_left(Point p)
{
    if (p==Point(1, 0))  return Point(0,  1);
    if (p==Point(0, 1))  return Point(-1, 0);
    if (p==Point(-1, 0)) return Point(0, -1);

    assert(p==Point(0, -1));

    return Point(1,  0);
}

int main()
{
    ifstream in("walk.in");

    vector<Point> all;

    int N; in>>N;
    all.push_back(Point(0, 0));
    all.push_back(Point(1, 0));

    for(int i=2; i<N+1; ++i)
    {
        Point delta = all[i-1] - all[i-2];
        Point next  = all[i-1] + get_left(delta);

        if(find(all.begin(), all.end(), next) != all.end())
            next    = all[i-1] + delta; 

        all.push_back(next);
    }

    ofstream out("walk.out"); 
    out<<all[N]<<endl;
}

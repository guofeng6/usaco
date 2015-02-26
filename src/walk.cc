// solution to 2015 amc 10b problem 24.
#include <fstream>
#include <vector>
#include <algorithm>
#include "assert.h"

using namespace std;

struct Point {
    int x;
    int y;
    Point(int a, int b):x(a), y(b) {}
    Point operator+(const Point & p) { return Point(x+p.x,  y+p.y); }
    Point operator-(const Point & p) { return Point(x-p.x,  y-p.y); }
    bool operator==(const Point & p) { return x==p.x && y == p.y; }
    Point & operator=(const Point & p) { x=p.x; y = p.y; return *this;}
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
    int a, b;
    in>>a>>b; all.push_back(Point(a, b));
    in>>a>>b; all.push_back(Point(a, b));

    for(int i=2; i<N+1; ++i) 
    {
        Point p     = all[i-1]-all[i-2];
        Point l     = get_left(p);
        Point next  = all[i-1] + l;

        if(find(all.begin(), all.end(), next) != all.end())
            next    = all[i-1]+p; 

        all.push_back(next);
    }

    ofstream out("walk.out"); 
    out<<all[N]<<endl;
}

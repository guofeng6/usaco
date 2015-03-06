// solution to 2015 amc 10b problem 24.
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
    Point(int a, int b):x(a), y(b) {}
    Point operator+(const Point & p)  const { return Point(x+p.x,  y+p.y); }
    Point operator-(const Point & p)  const { return Point(x-p.x,  y-p.y); }
    bool  operator==(const Point & p) const { return x==p.x && y == p.y; }
    Point & operator=(const Point & p) { x=p.x; y = p.y; return *this;}

    Point c90()     const { return Point(y,  -x); }
    Point c180()    const { return c90().c90();  }
    Point c270()    const { return c180().c90(); }
    Point mirror()  const { return Point(-x,  y); }
};

ostream & operator<<(ostream & o, const Point &p) { return o<<p.x<<' '<<p.y; }

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
        Point next  = all[i-1] + delta.c270();

        if(find(all.begin(), all.end(), next) != all.end())
            next    = all[i-1] + delta; 

        all.push_back(next);
    }

    ofstream out("walk.out"); 
    out<<all[N]<<endl;
}

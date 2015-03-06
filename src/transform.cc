/*
ID: guofeng2
TASK: transform
LANG: C++11
*/

#include <fstream>
#include <iostream>

using namespace std;

struct Point {
    int x, y;
    Point(int a, int b):x(a), y(b) {}
    Point operator+(const Point & p)  const { return Point(x+p.x,  y+p.y); }
    Point operator-(const Point & p)  const { return Point(x-p.x,  y-p.y); }
    bool  operator==(const Point & p) const { return x==p.x && y == p.y; }
    Point & operator=(const Point & p) { x=p.x; y = p.y; return *this;}

    //turn clockwise by 90
    Point turn()        const { return Point(y,  -x); }

    //x is vertical here so mirror changes sign of y
    Point mirror()      const { return Point(x,  -y); }
};

struct Matrix {
    int     N;
    string  data;

    Matrix(int n):N(n) {}
    ~Matrix(){}
    
    int    index(Point p)           const   { return p.x * N + p.y; }
    char & operator[](Point p)              { return data[index(p)];}
    char   operator[](Point p)      const   { return data[index(p)];}
    bool operator==(const Matrix& m)const   { return N==m.N && data==m.data; }

    Matrix turn()
    {
        Matrix m(N);
        for(int x=0; x<N; ++x)
            for(int y=0; y<N; ++y)
                m[Point(x,y).turn()+Point(0, N-1)] = (*this)[Point(x,y)];
        return m;
    }

    Matrix mirror()
    {
        Matrix  m(N);
        for(int x=0; x<N; ++x)
            for(int y=0; y<N; ++y)
                m[Point(x,y).mirror()+Point(0,N-1)] = (*this)[Point(x,y)];
        return m;
    }
};

istream & operator>>(istream & in, Matrix & m)
{
    string s;
    for(int x=0; x< m.N; ++x)
    {
        in>>s;
        for(int y=0; y<m.N; ++y)
            m[Point(x, y)]  = s[y];
    }
    return in;
}

ostream & operator<<(ostream & o, const Matrix & m)
{
    for(int x=0; x< m.N; ++x)
    {
        for(int y=0; y<m.N; ++y)
            o<<m[Point(x, y)];
        o<<endl;
    }
    return o;
}

ostream & operator<<(ostream & o, const Point &p) { return o<<p.x<<' '<<p.y; }

int main()
{
    ifstream in("transform.in");
    ofstream out("transform.out"); 

    int N;              in>>N;
    Matrix m(N);        in>>m;
    Matrix m_end(N);    in>>m_end;

    auto m_90       = m.turn();
    auto m_180      = m_90.turn();
    auto m_270      = m_180.turn();

    auto mm         = m.mirror();
    auto mm_90      = mm.turn();
    auto mm_180     = mm_90.turn();
    auto mm_270     = mm_180.turn();

#define _PRINT_(a)  cerr<<#a<<endl<<a<<endl;
    _PRINT_(m)
    _PRINT_(m_end)
    _PRINT_(mm)
    _PRINT_(mm_90)
    _PRINT_(mm_180)
    _PRINT_(mm_270)

    int x = 7;
    if      (m_90==m_end)   x = 1;
    else if (m_180==m_end)  x = 2;
    else if (m_270==m_end)  x = 3;
    else if (mm==m_end)     x = 4;
    else if (mm_90==m_end)  x = 5;
    else if (mm_180==m_end) x = 5;
    else if (mm_270==m_end) x = 5;
    else if (m==m_end)      x = 6;
    out<<x<<endl;
}


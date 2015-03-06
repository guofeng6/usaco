/*
ID: guofeng2
TASK: numtri
LANG: C++11
*/

#include <fstream>
#define _PRINT_(a)  out<<#a<<"="<<a<<endl;

using namespace std;

inline int index(int x, int y) { return x*(x+1)/2+y; }

struct Triangle
{
    int     N;
    int     M;
    int *   data;
    int *   max_sum;


    Triangle(int n):N(n), M(index(n, 0)) 
    { 
        data    = new int [M]; 
        max_sum = new int [M];
    }

    ~Triangle() {delete [] data;}
    
    int get_max_sum(int x, int y)
    {
        int ndx = index(x, y);
        if (x==N-1) return data[ndx];
        int m   = max_sum[ndx];
        if(m<0)
        {
            int s1          = get_max_sum(x+1, y);
            int s2          = get_max_sum(x+1, y+1);
            m               = data[ndx] + ((s1 > s2) ? s1 : s2);
            max_sum[ndx]    = m;
        }
        return m;
    }
};

istream & operator>>(istream & in, Triangle & t)
{ 
    for(int i=0; i<t.M; ++i) 
    {
        in>>t.data[i]; 
        t.max_sum[i] = -1;
    }
    return in;
}

int main()
{
    ifstream in("numtri.in");
    ofstream out("numtri.out");

    int N;          in>>N;
    Triangle t(N);  in>>t;

    out<<t.get_max_sum(0, 0)<<endl;
}

/*
ID: guofeng2
TASK: frac1
LANG: C++11
*/

#include <fstream>
#include <set>
#define _PRINT_(a)  out<<#a<<"="<<a<<endl;

using namespace std;

int common_factor(int a, int b)
{
    if(b==0) return a;
    int n = a % b;
    return (n==0)? b: common_factor(b, n);
}

struct Fraction{
    int a, b;

    Fraction(int _a, int _b)
    {
        auto c  = common_factor(_b, _a);
        a       = _a / c;
        b       = _b / c;
    }

    bool operator<(const Fraction & c) const { return a*c.b < b*c.a; }
};

ostream & operator<<(ostream & o, const Fraction & f)
{
    return o<<f.a<<'/'<<f.b;
}

int main()
{
    ifstream in("frac1.in");
    ofstream out("frac1.out");
    int N; in>>N;

    set<Fraction> all;

    all.insert(Fraction(0, 1));
    all.insert(Fraction(1, 1));

    for(int b=1; b<=N; ++b)
        for(int a=1; a<b; ++a)
            all.insert(Fraction(a, b));

    for(auto it=all.begin(); it!=all.end(); ++it)
        out<<*it<<endl;
}

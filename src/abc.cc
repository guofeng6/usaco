// solution to 2015 amc 10b problem 25.
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Calculator{
    ifstream in;
    ofstream out;

    int N;
public:

    Calculator(const string & name):in(name+".in"), out(name+".out")
    { in >> N; }

    void run() {
        solve_brute_force();
        solve_smarter();
    }

    void solve_brute_force() {
        int cnt = 0;
        for(int a=1; a<N; ++a)
            for(int b=a; b<N; ++b)
                for(int c=b; c<N; ++c)
                    if ((a * b * c) == 2*(a*b + b*c + c*a))
                        out<<a<<' '<<b<<' '<<c<<endl, ++cnt;;
        out<<"solve_brute_force cnt:"<<cnt<<endl;
    }

    //notice the equation is the same as: 1/2 = 1/a + 1/b + 1/c
    //so 3 <= a <= 6,  a <= b <= 4a/(a-2)
    void solve_smarter()
    {
        int cnt = 0;
        for(int a=3; a<=6; ++a)
            for(int b=a; b<=4*a/(a-2); ++b)
            {
                int x = 2*a*b; 
                int y = a*b-2*(a+b);
                if (y > 0 && x % y==0)
                    out<<a<<' '<<b<<' '<<(x/y)<<endl, ++cnt;
            }
        out<<"solve_smarter cnt:"<<cnt<<endl;
    }
};

int main() { Calculator("abc").run(); }

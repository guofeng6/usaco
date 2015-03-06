/*
ID: guofeng2
TASK: sort3
LANG: C++11
*/

#include <fstream>
#include <vector>
#include <iostream>
#define _PRINT_(a)  out<<#a<<"="<<a<<endl;

using namespace std;

struct number_range{
    int number;
    int begin;
    int end;

    number_range(int n, int b, int e):number(n), begin(b), end(e) {}

    bool is_in_range(int i) const {return begin<=i && i<end; }
};

class Calculator {
    int     N;  
    int *   all;
    int     swap_count;

    void swap(int i, int j)
    { int x=all[i]; all[i]=all[j]; all[j]=x; ++swap_count; }

    //strict swap only make swap when the numbers will be in their final 
    //position after the operation.
    //when this is no longer possible loose_swap is used, which means 
    //3-cycles are involved. 
    void strict_swap(number_range nr1, number_range nr2)
    {
        int i=nr1.begin, j=nr2.begin; 
        while(i<nr1.end && j<nr2.end)
        {
            while(all[i]!=nr2.number && i<nr1.end) ++i;
            while(all[j]!=nr1.number && j<nr2.end) ++j;
            if (i<nr1.end && j<nr2.end)
                swap(i++, j++);
        }
    }

    void loose_swap(number_range nr)
    {
        int i=nr.begin, j=nr.end;
        while(i<nr.end)
        {
            while(all[i]==nr.number && i<nr.end) ++i;
            if (nr.is_in_range(i))
            {
                //for loose swap if i has found one, j must also find one
                while(all[j]!=nr.number) ++j;
                swap(i++, j++);
            }
        }
    }

    ifstream in;
    ofstream out;
    int count[4];
public:
    Calculator(const string & name): in(name + ".in"), out(name + ".out")
    {
        in>>N;  
        all = new int [N];

        for(int i=0; i<4; ++i) count[i] = 0;

        for(int i=0; i<N; ++i) { 
            in>>all[i];
            ++count[all[i]];
        }
    }

    void run()
    {
        number_range nr1(1, 0,           count[1]);
        number_range nr2(2, count[1],    N-count[3]);
        number_range nr3(3, N-count[3],  N);

        swap_count  = 0;
        strict_swap(nr1, nr2);
        strict_swap(nr1, nr3);
        strict_swap(nr2, nr3);

        loose_swap(nr1);
        loose_swap(nr2);

        out<<swap_count<<endl;
    }
};

int main() { Calculator("sort3").run(); }

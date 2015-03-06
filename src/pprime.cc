/*
ID: guofeng2
TASK: pprime
LANG: C++11
*/

#include <fstream>
#include <vector>
#include <iostream>
#define _PRINT_(a)  out<<#a<<"="<<a<<endl;

using namespace std;

inline bool is_pal(int p)
{
    char buf[16];
    int n=0;

    while(p)
    {
        buf[n]  = p % 10 + '0'; 
        p       = p/10;
        ++n;
    }

    int n2  = n>>1;
    for(int i=0; i<n2; ++i)
        if (buf[i]!=buf[n-i-1])
            return false;
    return true;
}

struct PrimeChecker
{
    vector<int> prime_list;
    int     a, b;

    ofstream out; 

    PrimeChecker(int _a, int _b):a(_a), b(_b), out("pprime.out") 
    {
        prime_list.push_back(2);

        for(int n=3; n*n<=b; n+=2) //generate prime_list up to sqrt(b)
        {
            for(int i=0; i<prime_list.size(); ++i)
            {
                int p = prime_list[i];
                if (n % p == 0) 
                    break;
                if (p*p > n) 
                {
                    prime_list.push_back(n);
                    break;
                }
            }
        }
    }

    void print() 
    {
        for(int j=0; j<prime_list.size(); ++j)
            cerr<<prime_list[j]<<endl;
    }

    bool is_prime(int n) 
    {
        for(int j=0; j<prime_list.size(); ++j)
        {
            int p = prime_list[j];
            if (p*p > n)     break;
            if (n % p == 0) return false;
        }

        return true;
    }

    void check(int x)
    {
        if(x>=a && x<=b && is_prime(x))
            out<<x<<endl;
    }

    void make_and_check_pal(int p)
    {
        int r=0, f=1, n=p;

        while(p)
        {
            r   = r*10 + p % 10; 
            f   = f*10;
            p   = p/10;
        }

        for(int i=0; i<10; ++i)
        {
            int x  = n * f * 10 + i * f + r;
            check(x);
        }
    }
};

int main()
{
    ifstream in("pprime.in");
    int a, b;   in>>a>>b;

    PrimeChecker p(a, b); p.check(5); p.check(7); p.check(11);

    for(int i=1; i*i<=b; ++i)
        p.make_and_check_pal(i);
}


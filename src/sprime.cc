/*
ID: guofeng2
TASK: sprime
LANG: C++11
*/

#include <fstream>
#include <vector>
#include <iostream>
#define _PRINT_(a)  cerr<<#a<<"="<<a<<endl;

using namespace std;

struct PrimeChecker
{
    vector<int> prime_list;
    int     N;
    int     N10;

    ofstream out; 

    PrimeChecker(int _N):N(_N), N10(1), out("sprime.out") 
    {
        prime_list.push_back(2);

        for(int i=0; i<N; ++i) N10 = N10 * 10;

        for(int n=3; n*n<=N10; n+=2) //generate prime_list up to sqrt(N10)
        {
            for(auto p: prime_list)
            {
                if (n % p == 0) 
                    break;
                if (p * p > n) 
                {
                    prime_list.push_back(n);
                    break;
                }
            }
        }
    }

    void print() { for(auto p: prime_list) cerr<<p<<endl; }

    bool is_prime(int n) 
    {
        for(auto p: prime_list)
        {
            if (p * p > n)  break;
            if (n % p == 0) return false;
        }

        return true;
    }

    void make_sprime(int p, int len)
    {
        if (len==N)
            out<<p<<endl;
        else
        {
            for(int i=1; i<=9; i+=2)
            {
                int p1  = p * 10 + i;
                if (is_prime(p1))
                    make_sprime(p1, len+1);
            }
        }
    }
};

int main()
{
    ifstream in("sprime.in");
    int N;   in>>N;

    PrimeChecker p(N); 

    p.make_sprime(2, 1);
    p.make_sprime(3, 1);
    p.make_sprime(5, 1);
    p.make_sprime(7, 1);
}


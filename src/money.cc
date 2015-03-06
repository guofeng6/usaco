/*
ID: guofeng2
TASK: money
LANG: C++11
*/

/*
the note below is from usaco analysis page. it can be used to generate a
nice dp solution. 

We use dynamic programming to count the number of ways to make n cents with
the given coins. If we denote the value of the kth coin by c_k, then the
recurrence is:
      nway(n, k) = nway(n, k-1) + nway(n-c_k, k)
    This just says the number of ways to make n cents with the first k
    coins is the number of ways to make n cents using the first k-1 coins
    (i.e., without using the kth coin) plus the number of ways to make
    n-c_k cents using the first k coins. For the second set of ways, we
    then add the kth coin to arrive at a total of n cents.

    */


#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <assert.h>
#define _PRINT_(a)  cerr<<#a<<"="<<a<<endl;

using namespace std;

class Calculator{
    ifstream in;
    ofstream out;

    int V, N;
    vector<int>     coin_vec;

    long long *   data;
    int  index(int l, int n) const { return n*V + l; }
    long long get(int l, int n)   const { return data[index(l, n)]; }
    void set(int l, int n, long long val) { data[index(l, n)]=val; } 

    long long solve(int l, int n)
    {
        auto x  = get(l, n);
        if(x>=0) return x;
        if(n==0) 
            x   = 1;
        else{
            int m   = coin_vec[l];
            if(l==V-1)
                x   = (n % m == 0)?1:0;
            else
            {
                x   = 0;
                for(int i=0; i*m <= n; ++i)
                    x += solve(l+1, n-i*m);
            }
        }

        set(l, n, x);
        return x;
    }
public:

    Calculator(const string & name):in(name+".in"), out(name+".out")
    { 
        in >> V >> N; 
        for(int i=0, c; i<V; ++i, coin_vec.push_back(c)) in>>c;
        sort(coin_vec.begin(), coin_vec.end());
    }

    ~Calculator(){ delete [] data; }

    void run() { 
        data = new long long [(N+1) * V];
        for(int i=0; i<(N+1) * V; ++i) data[i] = -1;
        out<<solve(0, N)<<endl;;
    }
};

int main() { Calculator("money").run(); }

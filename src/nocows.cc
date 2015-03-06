/*
ID: guofeng2
TASK: nocows
LANG: C++11
*/

#include <fstream>
#include <assert.h>
#define _PRINT_(a)  out<<#a<<"="<<a<<endl;

using namespace std;

class Calculator{
    ifstream in;
    ofstream out;

    int N, K;
    int * solutions;

    int index(int k, int n) const       { return (k-1) * N + (n-1); }
    int   get(int k, int n) const       { return solutions[index(k, n)]; }
    void  set(int k, int n, int val)    { solutions[index(k, n)] = val; }

public:
    Calculator(const string & name):in(name+".in"), out(name+".out")
    { 
        in >> N >> K; 
        solutions   = new int [N*K];
    }

    ~Calculator() {delete [] solutions;}

    int mod(int n) {return n% 9901;}

    void solve_dp()
    {
        for(int n=1; n<=N; ++n)  
            set(1, n, n==1?1:0);  //set k=1 boundary
        
        for(int k=2; k<=K; ++k)
        {
            set(k, 1, 0); set(k, 2, 0);

            for(int n=3; n<=N; ++n)
            {
                int tot = 0;
                //remove the top node, we get two subtrees with n-1 node 
                //together, at lease one subtree is k-1 deep with p node, 
                //the other is k-1 deep or less with n-1-p node.
                for(int p=1; p<=n-2; p+=2)
                    //each tree must have odd number of nodes 
                    //so increase p by 2
                {
                    //one tree is k-1 deep the other is less deep
                    //multiply by 2, since we can swap the subtrees
                    //and get different results.
                    for(int q=1; q<=k-2; q++)
                        tot = mod(tot + 2*get(k-1, p) * get(q, n-p-1));
                    //it's possible to save this loop by using another
                    //array to keep track of the sum of all trees with 
                    //n nodes and depth below k.

                    //both subtrees are k-1 deep
                    //notice the lack of 2 factor here.
                    tot = mod(tot + get(k-1, p) * get(k-1, n-p-1));
                }

                set(k, n, tot);
            }
        }
        out<<get(K, N)<<endl;
    }

    void run() {
        solve_dp();
    }
};

int main() { Calculator("nocows").run(); }

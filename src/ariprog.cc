/*
ID: guofeng2
TASK: ariprog
LANG: C++11
*/

#include <fstream>
#include <vector>
#include <algorithm>
#define _PRINT_(a)  out<<#a<<"="<<a<<endl;

using namespace std;

int main()
{
    ifstream in("ariprog.in");
    ofstream out("ariprog.out");
    int N, M;
    in>>N>>M;
    int M2  = 2*M*M+1;

    bool bs_flag[M2];
    int  bs_vec[M2];
    int  vec_size  = 0;

    for(int i=0; i<M2; ++i) bs_flag[i]  = false;
    for(int p=0; p<=M; ++p)
        for(int q=0; q<=M; ++q)
        {
            auto n = p*p + q*q;
            if(!bs_flag[n]) 
            {
                bs_vec[vec_size]    = n;
                bs_flag[n] = true;
                ++vec_size;
            }
        }

    sort(bs_vec, bs_vec+vec_size);

    //using sorted array in place of a set for bisquares improves speed
    //to 4 folds.
    //it means iterating through the set is quite a bit more expensive.

    int found_count = 0;
    int max_step    = M2/(N-1);
    for(int step=1; step<=max_step; ++step)
    {
        for(int k=0; k<vec_size; ++k)
        {
            auto n0     = bs_vec[k];
            bool found  = true;

            for(int i=1; i<N; ++i)
            {
                auto n  = n0 + i * step;
                if (n >= M2 || !bs_flag[n])
                {
                    found = false;
                    break;
                }
            }

            if(found)
            {
                out<<n0<<' '<<step<<endl;
                ++found_count; 
            }
        }
    }

    if (found_count ==0)
        out<<"NONE"<<endl;
}

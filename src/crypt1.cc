/*
ID: guofeng2
TASK: crypt1
LANG: C++11
*/

#include <fstream>
#include <vector>

#define _PRINT_(a)  out<<#a<<"="<<a<<endl;

using namespace std;
class DigitSet{
    bool i_used[10];
public:
    DigitSet(const vector<int> & all)
    {
        for(int i=0; i<10; ++i)         i_used[i]       = false; 
        for(int i=0; i<all.size(); ++i) i_used[all[i]]  = true; 
    }

    bool is_valid(int n, int m)
    {
        int cnt = 0;
        while(n)
        {
            if (!i_used[n % 10])
                return false;
            n /= 10;
            ++ cnt; 
        }
        return (m==cnt);
    }
};

int main()
{
    ifstream in("crypt1.in");
    ofstream out("crypt1.out");
    int N;  in>>N;

    vector<int> all;
    for(int i=0; i<N; ++i)
    {
        int n; in>>n;
        all.push_back(n);
    }

    DigitSet ds(all);

    int valid_count = 0;

    for(int a=0; a<N; ++a)
    {
        for(int b=0; b<N; ++b)
        {
            for(int c=0; c<N; ++c)
            {
                int x  = 100 * all[a] + 10 * all[b] + all[c];
                for(int d=0; d<N; ++d)
                {
                    int y0 = all[d];
                    int z0 = y0 * x;

                    if(!ds.is_valid(z0, 3))    continue;

                    for(int e=0; e<N; ++e)
                    {
                        int y1  = all[e];
                        int z1  = y1 * x;
                        int y   = y0 * 10 + y1;
                        int z   = x * y;

                        if(ds.is_valid(z1, 3) && ds.is_valid(z, 4))
                            ++ valid_count;
                    }
                }
            }
        }
    }

    out<<valid_count<<endl;
}

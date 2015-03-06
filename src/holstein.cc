/*
ID: guofeng2
TASK: holstein
LANG: C++11
*/

#include <fstream>
#include <iostream>
#define _PRINT_(a)  out<<#a<<"="<<a<<endl;

using namespace std;

class Calculator{
    ifstream in;
    ofstream out;

    int Nv, Nf, select_count;

    int     * required;
    int     * food_info;
    int     * sum;

    bool    * selected;

    int index(int f, int v) const { return f * Nv + v;}
    int info (int f, int v) const { return food_info[index(f, v)]; }

    void select(int f)
    {
        selected[f] = true;     ++select_count;
        for(int v=0; v<Nv; ++v) sum[v]  += info(f, v);
    }

    void deselect(int f)
    {
        selected[f] = false;    --select_count;
        for(int v=0; v<Nv; ++v) sum[v]  -= info(f, v);
    }

    bool check_sum() const {
        for(int v=0; v<Nv; ++v)
            if (sum[v] < required[v]) return false;
        return true;
    }

    bool find_solution(int f0, int nf)
    {
        if (select_count == nf) 
            return check_sum();

        for(int f=f0; f<Nf; ++f)
        {
            if (!selected[f])
            {
                select(f);
                if(find_solution(f+1, nf))
                    return true;
                deselect(f);
            }
        }
        return false;
    }

    void reset()
    {
        for(int f=0; f<Nf; ++f) selected[f] = false;
        for(int v=0; v<Nv; ++v) sum[v]      = 0;
        select_count = 0;
    }

public:
    Calculator(const string &name):in(name+".in"), out(name+".out")
    {
        in >> Nv;
        required    = new int [Nv];
        sum         = new int [Nv];
        for(int i=0; i<Nv; ++i) 
            in >> required[i];

        in >> Nf;
        food_info   = new int [Nv * Nf];
        selected    = new bool[Nf];
        for(int f=0; f<Nf; ++f)
            for(int v=0; v<Nv; ++v)
                in >> food_info[index(f, v)];
    }

    void run()
    {
        reset();
        for(int nf=1; nf<=Nf; ++nf)
            if(find_solution(0, nf))
                break;

        out<<select_count<<' ';

        int n   = select_count;

        for(int f=0; f<Nf; ++f)
            if(selected[f])
                out<< f+1 <<(--n ? ' ' : '\n');
    }
};

int main() { Calculator("holstein").run(); }

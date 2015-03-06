/*
ID: guofeng2
TASK: hamming
LANG: C++11
*/

#include <fstream>
#include <vector>
#define _PRINT_(a)  out<<#a<<"="<<a<<endl;

using namespace std;

class Calculator{
    ifstream in;
    ofstream out;
    int N, B, D, B1;

    vector<int>     solution;

    int count_bits_fast(int n) const
    {
        n = ((n >> 1) & 0b01010101) + (n & 0b01010101);
        n = ((n >> 2) & 0b00110011) + (n & 0b00110011);
        n = ((n >> 4) & 0b00001111) + (n & 0b00001111);
        return n;
    }
    
    int count_bits(int n) const
    {
        int count = 0;
        for(int i=0; i<B; ++i)
            count += ((n>>i) & 1);
        return count;
    }
    

    bool check_solution(int n) const 
    {
        for(int i=0; i<solution.size(); ++i)
            if (count_bits_fast(solution[i] ^ n) < D)
                return false;
        return true;
    }

    bool find_solution(int n0)
    {
        if(solution.size()==N) return true;

        for(int n=n0; n<B1; ++n)
        {
            if(check_solution(n))
            {
                solution.push_back(n);
                if (find_solution(n+1)) return true;
                solution.pop_back();
            }
        }
        return false;
    }
public:

    Calculator(const string & name):in(name+".in"), out(name+".out")
    { in >> N >> B >> D; B1 = 1<<B; }

    void print_vec(const vector<int> & v)
    {
        for(int i=0; i<v.size(); ++i)
            out<<v[i]<<( (i%10!=9 && i <v.size()-1 )? ' ' : '\n');
    }

    void run()
    {
        if(find_solution(0))
            print_vec(solution);
    } 
};

int main()
{
    Calculator("hamming").run(); 
}

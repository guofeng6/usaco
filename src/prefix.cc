/*
ID: guofeng2
TASK: prefix
LANG: C++11
*/

#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#define _PRINT_(a)  cerr<<#a<<"="<<a<<endl;

using namespace std;

class Calculator{
    ifstream in;
    ofstream out;

    vector<string>  prim_vec;
    string          sequence;
    int             N;

    vector<string>  matches;

    int *           solution_map;

    void print() 
    {
        for(int i=0; i<matches.size(); ++i)
            cerr<<matches[i]<<' ';
        cerr<<endl;
    }

    //recursive solution 
    //find longest prefix starting from "start".
    int find_solution(int start)
    {
        if (start>=N) return 0;

        if (solution_map[start]>=0)
            return solution_map[start];

        int best = 0;

        for(int i=0; i<prim_vec.size(); ++i)
        {
            string  pi  = prim_vec[i];
            int     n   = pi.size();
            string  x   = sequence.substr(start, n);
            if(x==pi)
            {
                int m   = n + find_solution(start+n);
                if (m > best) best = m;
            }
        }

        solution_map[start] = best;
        return best;
    }

    //dynamic programming solution.
    int find_solution_dp()
    {
        solution_map[0] = 1;
        int best        = 0;
        for(int i=0; i<N; ++i)
        {
            if (solution_map[i]==1)
            {
                for(int j=0; j<prim_vec.size(); ++j)
                {
                    auto p  = prim_vec[j];
                    auto np = p.size();
                    if(p==sequence.substr(i, np))
                    {
                        solution_map[i+np] = 1;
                        if (i+np > best)
                            best   = i+np;
                    }
                }
            }
        }
        return best;
    }

public:

    struct prim_cmp{
        bool operator()(const string & a, const string & b) const 
        { return b.size()<a.size(); }
    };

    Calculator(const string & name):in(name+".in"), out(name+".out")
    { 
        string s;
        while(in>>s && s!=".")
            prim_vec.push_back(s);

        //the recursive call might run out of stack.
        //checking the longer primitive would help 
        //reducing the depth of the recursion.
        //
        //the dp solution would not have this problem.
        sort(prim_vec.begin(), prim_vec.end(), prim_cmp());

        while(in>>s)
            sequence += s;

        N = sequence.size();
        solution_map    =  new int [N+1];
        for(int i=0; i<N+1; ++i) solution_map[i] = -1;
    }

    ~Calculator() { delete [] solution_map; }

    void run() {
        //out<<find_solution(0)<<endl;
        out<<find_solution_dp()<<endl;
    }
};

int main() { Calculator("prefix").run(); }

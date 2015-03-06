/*
ID: guofeng2
TASK: subset
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <vector>
#define _PRINT_(a)  out<<#a<<"="<<a<<endl;

using namespace std;

class Calculator{
    ifstream in;
    ofstream out;

    int N;
    vector<int> solution;

    void print_solution()
    {
        for(int i=0; i<solution.size(); ++i)
            cerr<<solution[i]<<' ';
        cerr<<endl;
    }

    int index(int start, int target) { 
        int ndx = (target-1) * N + (start-1); 
        return ndx;
    }

    //find the number of subsets of start ... N, that sums up to "target".
    int find_solution(int start, int target)
    {
        if (start>N || target<start)    return 0;

        int   ndx   = index(start, target);
        auto  x     = solution_array[ndx];
        if (x >=0)      return x;

        if (start==target) 
            x = 1;
        else 
            x   = find_solution(start+1, target-start)
                + find_solution(start+1, target);

        solution_array[ndx] = x;
        return x;
    }

    int * solution_array;
    int   sum;
    int   M;
public:

    Calculator(const string & name):in(name+".in"), out(name+".out")
    { 
        in >> N; 
        sum             = N*(N+1) /2;
        M               = sum /2 * N;
        solution_array  = new int [M];

        for(int i=0; i<M; ++i)
            solution_array[i] = -1;
    }

    void run() { 
        if (sum%2)
            out<<'0'<<endl;
        else {
            //the solution without 1 is the same as that with 1.
            //so no need to divide by two for the result.
            out<<find_solution(2, sum/2)<<endl;
        }
    }
};

int main() { Calculator("subset").run(); }

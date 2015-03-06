/*
ID: guofeng2
TASK: zerosum
LANG: C++11
*/

#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <iostream>
#define _PRINT_(a)  cerr<<#a<<"="<<a<<endl;

using namespace std;

class Calculator{
    ifstream in;
    ofstream out;

    int N;
public:

    string make_solution(const string & digits, const string & operators)
    {
        string s; 
        s += digits[0];

        for(int i=0; i<N-1; ++i)
        {
            s += operators[i];
            s += digits[i+1];
        }

        return s;
    }

    template<class T>
    void print_vec(const vector<T> & v)
    {
        for(auto x: v)
            cerr<<"'"<<x<<"'"<<',';
        cerr<<endl;
    }

    int evaluate(const string & digits, const string & operators)
    {
        vector<int>  numbers; 
        vector<char> ops;

        numbers.push_back(digits[0]-'1'+1);
        int a, b;
        for(int i=0; i<N-1; ++i)
        {
            numbers.push_back(digits[i+1]-'1'+1);
            switch(operators[i])
            {
                case '+': 
                    ops.push_back('+'); break;
                case '-': 
                    ops.push_back('-'); break;
                case ' ': 
                    b = numbers.back(); numbers.pop_back(); 
                    a = numbers.back(); numbers.pop_back();
                    numbers.push_back(a*10+b); break;
            }
        }

        int result  = numbers[0];
        for(int i=0; i<ops.size(); ++i)
           result += (ops[i]=='+')?numbers[i+1]:-numbers[i+1];

        return result;
    }

    Calculator(const string & name):in(name+".in"), out(name+".out")
    { in >> N; }

    void run() { 
        vector<string> solutions;
        const char * operator_map = "+- "; 
        string digits       = string("123456789").substr(0, N);
        string operators    = digits.substr(0, N-1);

        int M = 1;
        for(int i=0; i<N-1; ++i) M *=3; 
        //loop through all N-1 digit numbers in base3
        for(int n=0; n<M; ++n) 
        {
            int m = n; 
            for(int j=0; j<N-1; ++j, m=m/3)
                operators[j] = operator_map[m%3];

            //out <<make_solution(digits, operators)
            //    <<'='<<evaluate(digits, operators)<<endl;
            if(evaluate(digits, operators)==0)
                solutions.push_back(make_solution(digits, operators));
        }

        sort(solutions.begin(), solutions.end());
        for(auto s: solutions)
            out<<s<<endl;
    }
};

int main() { Calculator("zerosum").run(); }

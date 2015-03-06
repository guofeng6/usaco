/*
ID: guofeng2
TASK: runround
LANG: C++11
*/

#include <fstream>
#include <iostream>
#define _PRINT_(a)  out<<#a<<"="<<a<<endl;

using namespace std;

class Calculator{
    ifstream in;
    ofstream out;

    int N;

    int get_digits(int m, int *digits, int *digit_cnt) {
        int cnt = 0;
        while(m) { 
            int d           = m % 10;
            digits[cnt++]   = d;
            m /= 10; 
            ++digit_cnt[d]; 
        }

        reverse_digits(digits, cnt);
        return cnt;
    }

    bool check_digit_cnt(int *cnt)
    {
        for(int i=0; i<10; ++i)
            if (cnt[i] > 1) return false;
        return true;
    }

    //reverse digits
    void reverse_digits(int *digits, int cnt)
    {
        for(int i=0; i<cnt/2; ++i)
        {
            int x           = digits[i]; 
            digits[i]       = digits[cnt-i-1]; 
            digits[cnt-i-1] = x;
        }
    }

    void print_arr(int *a, int cnt)
    {
        for(int i=0; i<cnt; ++i)
            cerr<<a[i]<<' ';
        cerr<<endl;
    }

    bool check(int m)
    {
        int digits[10], digit_cnt[10], walk_cnt[10];

        for(int i=0; i<10; ++i) 
            digits[i] = walk_cnt[i] = digit_cnt[i] = 0;

        int cnt = get_digits(m, digits, digit_cnt);

        //print_arr(digits, cnt);
        //print_arr(digit_cnt, 10);
        //digits not unique.
        if(digit_cnt[0]>0)              return false; 
        if(!check_digit_cnt(digit_cnt)) return false;

        int cur = 0;
        for(int i=0; i<cnt; ++i)
        {
            int x = digits[cur]; ++walk_cnt[x]; 
            cur   = (cur + x) % cnt; 
        }

        if(!check_digit_cnt(walk_cnt)) return false;

        return (cur==0);
    }
public:

    Calculator(const string & name):in(name+".in"), out(name+".out")
    { in >> N ; }

    void run() {
        int m = N;
        while(true)
            if (check(++m))
                break;
        out<<m<<endl;
    }
};

int main() { Calculator("runround").run(); }

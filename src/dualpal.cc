/*
ID: guofeng2
TASK: dualpal
LANG: C++11
*/

#include <fstream>

using namespace std;

const char * num_map  = "0123456789ABCDEFGHIJKLMNOPQ";

string get_string(int n, int B)
{
    string s;
    while(n)
    {
        s   += num_map[n%B];
        n   =  n/B; 
    }
    return s;
}

string reverse_string(const string & s)
{
    string r;
    for(int i=0; i<s.size(); ++i)
        r += s[s.size()-1-i];
    return r;
}

int main()
{
    ifstream in("dualpal.in");
    ofstream out("dualpal.out");
    int N, S;
    in>>N>>S;

    int s   = S+1;
    int n   = 0;
    while(n<N)
    {
        int pal_cnt = 0;
        for(int b=2; b<=10; ++b)
        {
            auto ss = get_string(s, b);
            if(reverse_string(ss)==ss)
                ++pal_cnt;
        }
        if(pal_cnt >= 2)
        {
            out<<s<<endl;
            ++n;
        }

        ++s;
    }
}

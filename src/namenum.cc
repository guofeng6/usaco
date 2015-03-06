/*
ID: guofeng2
TASK: namenum
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <set>

#define _PRINT_(a)  cerr<<#a<<endl<<a<<endl;

using namespace std;

const char * key_map [] =  { 
    "ABC", //2
    "DEF", //3
    "GHI", //4
    "JKL", //5
    "MNO", //6
    "PRS", //7
    "TUV", //8
    "WXY"  //9
};

class Calculator{
    ifstream in;
    ofstream out;

    string num; 
public:

    Calculator(const string & name):in(name+".in"), out(name+".out")
    { in >> num ; }

    void solve_slow()
    {
        ifstream din("dict.txt");
        set<string> dict;
        string s;
        while(din) { din>>s; dict.insert(s); }

        int N = 1;

        //get the total number of possibilities 
        for(int i=0; i<num.size(); ++i) N *= 3;

        auto name = num; 
        set<string> found;

        for(int i=0; i<N; ++i)  //loop through all numbers below N in base 3.
        {
            int n   = i;
            for(int j=0; j<num.size(); ++j, n/=3)
                name[j] = key_map[num[j]-'2'][n % 3];

            if (dict.find(name) != dict.end())
                found.insert(name);
        }

        if (found.empty())
            out<<"NONE"<<endl;
        else
            for(auto i=found.begin(); i!=found.end(); ++i)
                out<<*i<<endl;
    }

    void solve_smart(){
        char m[256];
        for(int i=0; i<256; ++i) m[i] = 0;
        for(int i=2; i<=9;  ++i)
            for(int j=0; j<3; ++j)
                m[key_map[i-2][j]] = i + '2' - 2;

        ifstream din("dict.txt");
        auto mapped_word    = num;
        int  count          = 0;

        string word;

        while(din)
        {
            din>>word;
            if (word.size()!=num.size()) continue;

            for(int i=0; i<num.size(); ++i)
                mapped_word[i] = m[word[i]];

            if(mapped_word==num) 
                out<<word<<endl, ++count;
        }

        if(count==0)
            out<<"NONE"<<endl;
    }

    void run() 
    { 
        solve_slow();
        solve_smart();
    }
};

int main()
{
    //put all words from the dictionary in a set.
    Calculator("namenum").run();
}


/*
ID: guofeng2
TASK: lamps
LANG: C++11
*/

#include <fstream>
#include <queue>
#define _PRINT_(a)  out<<#a<<"="<<a<<endl;

using namespace std;

class Calculator{
    ifstream in;
    ofstream out;

    int N, C;

    string      lamps_final;
    string      lamps_initial;

    priority_queue<string, vector<string>, greater<string> > solutions;

    void input_on_off(char on_off)
    {
        while(true)
        {
            int x; in>>x;
            if (x == -1)
                break;
            else 
                lamps_final[x-1] = on_off;
        }
    }

    char toggle(char x) { return 1 - (x-'0') + '0'; }

    bool is_valid(const string & lamps)
    {
        for(int i=0; i<N; ++i)
        {
            if (lamps_final[i] == '2')      continue;
            if (lamps_final[i] != lamps[i]) return false;;
        }

        return true;
    }

    void toggle(string & lamps, int start, int step) 
    {
        for(int i=start; i<N; i+=step)
            lamps[i] = toggle(lamps[i]);
    }

    void check(const string & buttons)
    {
        string lamps    = lamps_initial;

        if(buttons[0]=='1') toggle(lamps, 0, 1);
        if(buttons[1]=='1') toggle(lamps, 1, 2);
        if(buttons[2]=='1') toggle(lamps, 0, 2); 
        if(buttons[3]=='1') toggle(lamps, 0, 3);

        if(is_valid(lamps))
            solutions.push(lamps);
    }

public:

    Calculator(const string & name):in(name+".in"), out(name+".out")
    { 
        in >> N >> C;
        lamps_final   = string(N, '2');
        lamps_initial = string(N, '1');
        input_on_off('1');
        input_on_off('0');
    }

    void check0() { check("0000"); }

    void check1() { 
        check("0001");
        check("0010");
        check("0100");
        check("1000");
    }

    void check2() { 
        check("0011");
        check("0101");
        check("1001");
        check("0110");
        check("1010");
        check("1100");
    }

    void check3()
    {
        check("0111");
        check("1011");
        check("1101");
        check("1101");
    }

    void check4() { check("1111"); }

    void run() {
        if (C==0)           { check0(); }
        else if (C==1)      { check1(); }
        else if (C==2)      { check0(); check2(); }
        else if (C%2==0)    { check0(); check2(); check4(); }
        else if (C%2==1)    { check1(); check3(); }

        if(solutions.size()>0)
            while(!solutions.empty())
            {
                out<<solutions.top()<<endl;
                solutions.pop();
            }
        else
            out<<"IMPOSSIBLE"<<endl;
    };
};

int main() { Calculator("lamps").run(); }

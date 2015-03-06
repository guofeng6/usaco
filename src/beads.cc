/*
ID: guofeng2
TASK: beads
LANG: C++
*/

#include <fstream>
#include <iostream>
//a little change 

using namespace std;

class Necklace{
    int     N;
    string  b;

    char get_one(int p) { return b[(p+N) % N]; }

    int collect_one_way(int p, int sign)
    {
        char first    =  get_one(p);
        int  n        =  1;
        p             += sign;
        for(; n<N; n++, p+=sign)
        {
            char ch     = get_one(p);
            if(ch=='w');
            else if (first == 'w')  first = ch;
            else if (ch==first);
            else break;
        }

        return n;
    }

public:
    Necklace(const string & s): N(s.size()), b(s){}

    int max_collectable() 
    {
        int max_count = 0;

        for(int p=0; p<N; ++p)
        {
            int n = collect_one_way(p, 1) + collect_one_way(p-1, -1);
            if (n > max_count)
                max_count = n;
        }

        if (max_count > N) 
            max_count = N;

        return max_count;
    }
};

int main()
{
    int      N;
    string   b;

    ifstream("beads.in") >>N>>b;
    ofstream("beads.out")<<Necklace(b).max_collectable();
}

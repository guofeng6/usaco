/*
ID: guofeng2
TASK: barn1
LANG: C++11
*/

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ifstream in("barn1.in");
    ofstream out("barn1.out");
    int M, S, C;    in>>M>>S>>C;

    bool stall_has_cow[S];

    for(int i=0; i<S; ++i) stall_has_cow[i] = false;

    for(int i=0; i<C; ++i)
    {
        int c;      in>>c; 
        stall_has_cow[c-1]    = true;
    }

    vector<int> empty_blocks;
    //walk through stalls
    int empty_stall_count = 0;
    if (stall_has_cow[0]) 
        empty_blocks.push_back(0);

    for(int i=0; i<S; ++i)
    {
        if (stall_has_cow[i])
        {
            if(empty_stall_count>0)
            {
                empty_blocks.push_back(empty_stall_count);
                empty_stall_count = 0;
            }
        } else 
        {
            ++empty_stall_count;
        }
    }

    S   -= empty_blocks.front(); //first empty block should not be covered
    S   -= empty_stall_count;    //last empty block should not be covered   

    //skip the first empty block and sort the rest.
    sort(empty_blocks.begin()+1, empty_blocks.end(), std::greater<int>());

    int  removable = (empty_blocks.size()<M)?(empty_blocks.size()-1):(M-1);

    for(int i=0; i<removable; ++i) 
        S -= empty_blocks[i+1];

    out<<S<<endl;
}

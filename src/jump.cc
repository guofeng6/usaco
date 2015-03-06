// solution to 2015 amc 10b problem 21.
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int get_jumps(int n, int step) 
{ 
    return (n + step - 1) / step; 
}

int main()
{
    ifstream in("jump.in");
    ofstream out("jump.out");

    int N; in>>N;
    int sum = 0;

    for(int i=1; i < N; ++i)
    {
        if (get_jumps(i, 2) == get_jumps(i, 5) + 19)
        {
            sum += i;
            out<<i<<endl;
        }
    }

    out<<"sum:"<<sum<<endl;
}

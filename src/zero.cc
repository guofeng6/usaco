// solution to 2015 amc 10b problem 23.
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int get_zero_cnt(int n)
{
    int cnt = 0;
    while(n>0)
    {
        n   =  n/5;
        cnt += n;
    }
    return cnt;
}

int main()
{
    ifstream in("zero.in");
    ofstream out("zero.out"); 

    int N; in>>N;
    int cnt     = 0;
    int sum     = 0;
    int n       = 5;

    while(cnt < N)
    {
        if(get_zero_cnt(n) * 3 == get_zero_cnt(2*n))
        {
            ++cnt;
            sum += n;
            out<<n<<endl;
        }
        ++n;
    }
    out<<"sum:"<<sum<<endl;
}

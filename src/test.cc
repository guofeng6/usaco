/*
ID: guofeng2
TASK: test
LANG: C++
*/

#include <fstream>

using namespace std;

int main()
{
    ifstream in("test.in");
    int a, b;
    in>>a>>b;
    ofstream out("test.out");
    out<<(a+b)<<endl;
    return 0;
}

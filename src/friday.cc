/*
ID: guofeng2
TASK: friday
LANG: C++
*/

#include <fstream>
#include <iostream>

using namespace std;

bool is_leap_year(int y)
{
    if(y%400 == 0)
        return true;
    else if(y%100==0)
        return false;
    else if(y%4==0)
        return true;
    else 
        return false;
}

int days_for_month_of_year(int m, int y)
{
    int x;
    switch(m+1)
    {
        case 1:   x   = 31; break;
        case 2:   x   = is_leap_year(y)?29:28; break;
        case 3:   x   = 31; break;
        case 4:   x   = 30; break;
        case 5:   x   = 31; break;
        case 6:   x   = 30; break;
        case 7:   x   = 31; break;
        case 8:   x   = 31; break;
        case 9:   x   = 30; break;
        case 10:  x   = 31; break;
        case 11:  x   = 30; break;
        case 12:  x   = 31; break;
    }
    return x;
}

int main()
{
    ifstream in("friday.in");
    ofstream out("friday.out");
    int N; in>>N;

    int count[7];
    for(int i=0; i<7; ++i) count[i] = 0;

    int d = 13;
    count[d%7] ++;

    for(int y=0; y<N; ++y)
    {
        for (int m = 0; m < 12; ++m)
        {
            d += days_for_month_of_year(m, y+1900);
            count[d%7] ++;
        }
    }

    count[d%7]--;

    for(int i=0; i<6; ++i)
        out<<count[(i+6)%7]<<' ';

    out<<count[(6+6)%7]<<endl;

    return 0;
}

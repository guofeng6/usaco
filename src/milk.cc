/*
ID: guofeng2
TASK: milk 
LANG: C++11
*/

#include <fstream>
#include <set>
using namespace std;

struct Farmer{
    int price;
    int amount;
    Farmer(int p, int a) : price(p), amount(a) {}
    bool operator<(const Farmer & f) const {return price < f.price; }
};

int main()
{
    ifstream in("milk.in");
    ofstream out("milk.out");

    int N, M;   in>>N>>M;

    multiset<Farmer>     farmers;
    
    for(int i=0; i<M; ++i)
    {
        int p, a;
        in >> p >> a;
        farmers.insert(Farmer(p, a));
    }

    int cost = 0;

    for(auto i = farmers.begin(); i!=farmers.end() && N > 0; ++i)
    {
        int n   = (N > i->amount)?i->amount:N;
        N       -= n;
        cost    += i->price * n;
    }

    out<<cost<<endl;
}

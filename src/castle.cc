/*
ID: guofeng2
TASK: castle
LANG: C++11
*/

#include <fstream>
#include <map>
#include <vector>
#include <iostream>
#define _PRINT_(a)  out<<#a<<"="<<a<<endl;

//+x is south
//+y is east

using namespace std;

//1: wall to the west   -y
//2: wall to the north  -x
//4: wall to the east   +y
//8: wall to the south  +x

class Module;

vector<Module *> module_vec;

int X, Y;

int index(int x, int y) {
    if(0<=x && x<X && 0<=y && y<Y) 
        return x * Y + y; 
    return -1;
}

Module * get_module(int x, int y)   {
    int ndx = index(x, y);
    return (ndx < 0)? 0 : module_vec[index(x, y)]; 
}

struct Module
{
    int  x, y;
    int  component;

    int  w;

    Module(int _x, int _y, int _w)
        :x(_x), y(_y), w(_w), component(0) {}

    Module * nbr_to_minus_y() const  { return (w & 1)? 0: get_module(x, y-1); }
    Module * nbr_to_minus_x() const  { return (w & 2)? 0: get_module(x-1, y); }
    Module * nbr_to_plus_y()  const  { return (w & 4)? 0: get_module(x, y+1); }
    Module * nbr_to_plus_x()  const  { return (w & 8)? 0: get_module(x+1, y); }
};

void reset_components()
{
    for(int i=0; i<X*Y; ++i) 
        module_vec[i]->component    = 0;
}

bool pre_visit(Module * p) 
{
    if(p && p->component==0)
    {
        p->component  = -2;
        return true;
    }
    return false;
}

void depth_first_search(Module * p, int component) 
{
    if(!p || p->component!=0)  return;
    p->component = component;
    depth_first_search(p->nbr_to_plus_x(),  component);
    depth_first_search(p->nbr_to_plus_y(),  component);
    depth_first_search(p->nbr_to_minus_x(), component);
    depth_first_search(p->nbr_to_minus_y(), component);
}

void find_components_dfs()
{
    int num_component = 0;

    for(int i=0; i<X*Y; ++i)
    {
        auto p = module_vec[i];
        if(p->component==0)
        {
            ++num_component;
            depth_first_search(p, num_component);
        }
    }
}

void flood_fill_visit(int component)
{
    int num_visited;
    do
    {
        num_visited = 0;
        for(int i=0; i<X*Y; ++i) 
        {
            auto p = module_vec[i];
            if (p->component == -2)
            {
                ++num_visited;
                p->component = component;

                pre_visit(p->nbr_to_plus_x());
                pre_visit(p->nbr_to_plus_y());
                pre_visit(p->nbr_to_minus_x());
                pre_visit(p->nbr_to_minus_y());
            }
        }
    } while(num_visited >0); 
}

void find_components_ffs()
{
    int num_component = 0;

    for(int i=0; i<X*Y; ++i)
    {
        auto p = module_vec[i];
        if(pre_visit(p))
        {
            ++num_component;
            flood_fill_visit(num_component);
        }
    }
}

void get_component_map(map<int, int> & m)
{
    for(int i=0;i<X*Y; ++i)
    {
        auto p  = module_vec[i];
        auto it = m.find(p->component);
        if(it==m.end())
            m.insert(make_pair(p->component, 1));
        else
            it->second += 1;
    }
}

int main()
{
    ifstream in("castle.in");
    ofstream out("castle.out");

    in>>Y>>X;

    for(int i=0; i<X*Y; ++i) module_vec.push_back(0); 
    for(int x=0; x<X;   ++x)
        for(int y=0; y<Y; ++y)
        {
            int w;  in>>w;
            module_vec[index(x, y)] = new Module(x, y, w);
        }

    map<int, int> component_map;

    int max_count = 0;
    {
        reset_components();
        //find_components_ffs();
        find_components_dfs();
        get_component_map(component_map);

        for(auto it = component_map.begin(); it!=component_map.end(); ++it)
            if(it->second > max_count)
                max_count = it->second;

        out<<component_map.size()<<endl;
        out<<max_count<<endl;
    }

    max_count  = 0;
    int  max_x, max_y;       
    char max_wall;

    for(int y=0; y<Y; ++y)
        for(int x=X-1; x>=0; --x) //priority requirement of the problem spec
        {
            auto p     = get_module(x, y);
            if(auto q  = get_module(x-1, y))
            {
                if(p->component != q->component)
                {
                    int  n  = component_map[p->component] + component_map[q->component];
                    if (n>max_count)
                    {
                        max_count   = n;
                        max_x       = x;
                        max_y       = y;
                        max_wall    = 'N';
                    }
                }
            }

            if(auto q = get_module(x, y+1))
            {
                if(p->component != q->component)
                {
                    int  n  = component_map[p->component] + component_map[q->component];
                    if (n>max_count)
                    {
                        max_count   = n;
                        max_x       = x;
                        max_y       = y;
                        max_wall    = 'E';
                    }
                }
            }
        }
    out<<max_count<<endl;
    out<<(max_x+1)<<' '<<(max_y+1)<<' '<<max_wall<<endl;
}

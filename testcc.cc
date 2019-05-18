#include <iostream>
#include <cstdio>
using namespace std;

#include "heuristic_fix.cc"

const char *filename = "rec.out";
int main(int argc, char const *argv[])
{
    FILE *f = fopen(filename, "w+");
    RecList list{};
    list.push_back(RecTuple{5, 3});
    list.push_back(RecTuple{5, 3});
    list.push_back(RecTuple{2, 4});
    list.push_back(RecTuple{30, 8});
    list.push_back(RecTuple{10, 20});
    list.push_back(RecTuple{20, 10});
    list.push_back(RecTuple{5, 5});
    list.push_back(RecTuple{5, 5});
    list.push_back(RecTuple{10, 10});
    list.push_back(RecTuple{10, 5});
    list.push_back(RecTuple{6, 4});
    list.push_back(RecTuple{1, 10});
    list.push_back(RecTuple{8, 4});
    list.push_back(RecTuple{6, 6});
    list.push_back(RecTuple{20, 14});
    auto ans = ph(30, list, width);
    fprintf(f, "%d %d\n", ans.size(), 4);
    for(auto i: ans) {
        cout<<"X:"<<i.x<<" ";
        cout<<"Y:"<<i.y<<" "; 
        cout<<"W:"<<i.w<<" ";
        cout<<"H:"<<i.h<<" "<<endl;
        fprintf(f, "%d %d %d %d\n", i.x, i.y, i.w, i.h);
    }
    
    fclose(f);
    return 0;
}

#include "heuristic.hpp";

#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    RecList list { };
    for(auto i = 0; i < 5; i++)
        list.push_back(RecTuple{i + 1 + i % 2, i + 2 - i % 2});
    
    ph(120, list, width);

    return 0;
}

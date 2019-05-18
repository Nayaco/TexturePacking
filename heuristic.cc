
#include "heuristic.hpp"
#include <iostream>
RecVec& ph(uint32_t width, const RecList& rectangles, Order order) {
    uint32_t sortOrder = (uint32_t)order;
    
    RecVec result ();

    RecList remain { rectangles };
    
    for(auto idx: remain) 
        if(idx[0] > idx[1])
            ~idx;
    // for(auto idx: remain) 
    //     std::cout<<idx[0]<<' '<<idx[1]<<std::endl;    

    PodVec sortedIndices(sort_indexes<RecTuple, RecLess<0>>(remain));
    for(auto idx: sortedIndices)
        std::cout<<idx.value<<' '<<remain[idx.value][0]<<' '<<remain[idx.value][1]<<std::endl;
    
    uint32_t  x, y, w, h, H;
    x = y = w = h = H = 0;
    
    // while (!sortedIndices.empty())
    // {
    //     auto idx = sortedIndices.top();
    //     if(idx.isNull && idx.nextPos == -1)break;
    //     std::cout<<idx.value<<std::endl;
    //     sortedIndices.pop();
    //     std::cout<<"pop"<<std::endl;
    //     for(auto idx: sortedIndices)
    //     std::cout<<idx.isNull<<' '<<idx.nextPos<<std::endl;


    // }

    while(1) {
        auto idx = sortedIndices.top();
        if(idx.isNull && idx.nextPos == -1) break;
        auto r = remain[idx.value];
        if(r[1] > width){ 
            result[idx.value] =

        } 

    }

    
    
    return result;
} 


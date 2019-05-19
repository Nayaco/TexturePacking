#ifndef NFDH
#define NFDH 1

#include "rectangleVec.hpp"
#include <cstdlib>
using namespace std;

tuple<int32_t, RecVec> nfdh_OG(int32_t width, const RecList &rectangles) {
    int32_t recListSize = rectangles.size();
    int32_t ceilL = 0;
    int32_t YL = 0;
    int32_t HL = 0;
    int32_t WL = 0;

    RecVec result { };
        
    RecList remain { rectangles };

    auto sortedIndices = sort_indexes<RecTuple, RecLess<height>>(remain);
    
    for(auto idx = 0; idx < recListSize; ++idx) {
        auto i = sortedIndices[idx];
        auto flag = 0;
        auto rot = i < recListSize ? 1 : -1;
        if(HL >= remain[i][1] && width - WL >= remain[i][0]) {
            result.push_back(Rectangle{
                WL, YL, remain[i][0], remain[i][1]});
            HL = remain[i][1];
            WL += remain[i][0];
        } else {
            result.push_back(Rectangle{
                0, ceilL, remain[i][0], remain[i][1]});
            ceilL += remain[i][1];
            HL = remain[i][1];
            WL = remain[i][0];
            YL = ceilL - remain[i][1];
        }
    }
    return make_tuple(ceilL, result);
}

template<Order order = height>
tuple<int32_t, RecVec> nfdh_RG(int32_t width, const RecList &rectangles) {
    int32_t recListSize = rectangles.size();
    int32_t ceilL = 0;
    int32_t YL = 0;
    int32_t HL = 0;
    int32_t WL = 0;

    RecVec result { };
        
    RecList remain { rectangles };

    for(auto i = 0; i < remain.size(); ++i)
        if(order == height)
            if(remain[i][0] < remain[i][1])
                remain[i] = ~remain[i];
        else
            if(remain[i][0] > remain[i][1])
                remain[i] = ~remain[i];
                
    auto sortedIndices = sort_indexes<RecTuple, RecLess<height>>(remain);
    
    for(auto idx = 0; idx < recListSize; ++idx) {
        auto i = sortedIndices[idx];
        auto flag = 0;
        auto rot = i < recListSize ? 1 : -1;
        if(HL >= remain[i][1] && width - WL >= remain[i][0]) {
            result.push_back(Rectangle{
                WL, YL, remain[i][0], remain[i][1]});
            HL = remain[i][1];
            WL += remain[i][0];
        } else {
            result.push_back(Rectangle{
                0, ceilL, remain[i][0], remain[i][1]});
            ceilL += remain[i][1];
            HL = remain[i][1];
            WL = remain[i][0];
            YL = ceilL - remain[i][1];
        }
    }
    return make_tuple(ceilL, result);
}


#endif
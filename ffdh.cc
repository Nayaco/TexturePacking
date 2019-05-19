#ifndef FFDH
#define FFDH 1

#include "rectangleVec.hpp"
#include <cstdlib>
using namespace std;

tuple<int32_t, RecVec> ffdh_OG(int32_t width, const RecList &rectangles) {
    int32_t recListSize = rectangles.size();
    int32_t ceilL = 0;
    std::vector<int32_t> YL { };
    std::vector<int32_t> HL { };
    std::vector<int32_t> WL { };

    RecVec result { };
        
    RecList remain { rectangles };

    auto sortedIndices = sort_indexes<RecTuple, RecLess<height>>(remain);
    
    for(auto idx = 0; idx < recListSize; ++idx) {
        auto i = sortedIndices[idx];
        auto flag = 0;
        auto rot = i < recListSize ? 1 : -1;
        for(auto j = 0; j < HL.size(); ++j) {
            if(HL[j] >= remain[i][1] && width - WL[j] >= remain[i][0]) {
                result.push_back(Rectangle{
                    WL[j], YL[j], remain[i][0], remain[i][1]});
                flag = 1;
                HL[j] = remain[i][1];
                WL[j] += remain[i][0];
                break;
            }
        }
        if(!flag) {
            result.push_back(Rectangle{
                0, ceilL, remain[i][0], remain[i][1]});
            ceilL += remain[i][1];
            HL.push_back(remain[i][1]);
            WL.push_back(remain[i][0]);
            YL.push_back(ceilL - remain[i][1]);
        }
    }
    return make_tuple(ceilL, result);
}

template<Order order = height>
tuple<int32_t, RecVec> ffdh_RG(int32_t width, const RecList &rectangles) {
    int32_t recListSize = rectangles.size();
    int32_t ceilL = 0;
    std::vector<int32_t> YL { };
    std::vector<int32_t> HL { };
    std::vector<int32_t> WL { };

    RecVec result { };
        
    RecList remain { rectangles };

    for(auto i = 0; i < remain.size(); ++i)
        if(order == height)
            if(remain[i][0] < remain[i][1])
                remain[i] = ~remain[i];
        else
            if(remain[i][0] > remain[i][1])
                remain[i] = ~remain[i];

    auto sortedIndices = sort_indexes<RecTuple, RecLess<order>>(remain);
    
    for(auto idx = 0; idx < recListSize; ++idx) {
        auto i = sortedIndices[idx];
        auto flag = 0;
        auto rot = i < recListSize ? 1 : -1;
        for(auto j = 0; j < HL.size(); ++j) {
            if(HL[j] >= remain[i][1] && width - WL[j] >= remain[i][0]) {
                result.push_back(Rectangle{
                    WL[j], YL[j], remain[i][0], remain[i][1]});
                flag = 1;
                HL[j] = remain[i][1];
                WL[j] += remain[i][0];
                break;
            }
        }
        if(!flag) {
            result.push_back(Rectangle{
                0, ceilL, remain[i][0], remain[i][1]});
            ceilL += remain[i][1];
            HL.push_back(remain[i][1]);
            WL.push_back(remain[i][0]);
            YL.push_back(ceilL - remain[i][1]);
        }
    }
    return make_tuple(ceilL, result);
}

#endif
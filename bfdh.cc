#ifndef BFDH
#define BFDH 1

#include "rectangleVec.hpp"
#include <cstdlib>
using namespace std;

/**
 * Implement of BFDH to solving texture packing problem(OG)
 * 
 * @ Function:
 * [int32, [x:int32, y:int32, w:int32, h:int32][]] ph(int32, [w:int32, h:int32][])
 * 
 * @ Arguments:
 * Argument name                |              Type            |           Deccription 
 * width                        |         int32                | :the width of strip 
 * rectangles                   |         RecList              | :rectangle dataset
 * 
 * @ Return Value
 * height                       |         int32                | :the height of strip
 * rectanglePosition            |         RecVec               | :the result of each recrangle
 * 
 * @ Example:
 * 
 * int main() {
 *      RecList input { };
 *      int32_t height;
 *      RecVec  rectangles { };
 *      input.push_back(RecTuple{1, 2});
 *      input.push_back(RecTuple{2, 3});
 *      input.push_back(RecTuple{3, 4});
 *      input.push_back(RecTuple{4, 5});
 *      
 *      std::tie(height, rectangles) = bfdh_OG(10, input);
 * }
**/
tuple<int32_t, RecVec> bfdh_OG(int32_t width, const RecList &rectangles) {
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
        auto best = -1;
        auto rot = i < recListSize ? 1 : -1;
        for(auto j = 0; j < HL.size(); ++j) {
            if(HL[j] >= remain[i][1] && width - WL[j] >= remain[i][0]) {
                if(best == -1 || WL[j] > WL[best])
                    best = j;
            }
        }
        if(best > -1) {
            result.push_back(Rectangle{
                WL[best], YL[best], remain[i][0], remain[i][1]});
            HL[best] = remain[i][1];
            WL[best] += remain[i][0];
        }else {
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


/**
 * Implement of BFDH to solving texture packing problem(RG)
 * 
 * @ Function:
 * [int32, [x:int32, y:int32, w:int32, h:int32][]] ph(int32, [w:int32, h:int32][])
 * 
 * @ Arguments:
 * Argument name                |              Type            |           Deccription 
 * template argument: order     |         width/height         | :to specific sorting column of rectangles
 * width                        |         int32                | :the width of strip 
 * rectangles                   |         RecList              | :rectangle dataset
 * 
 * @ Return Value
 * height                       |         int32                | :the height of strip
 * rectanglePosition            |         RecVec               | :the result of each recrangle
 * 
 * @ Example:
 * 
 * int main() {
 *      RecList input { };
 *      int32_t height;
 *      RecVec  rectangles { };
 *      input.push_back(RecTuple{1, 2});
 *      input.push_back(RecTuple{2, 3});
 *      input.push_back(RecTuple{3, 4});
 *      input.push_back(RecTuple{4, 5});
 *      
 *      std::tie(height, rectangles) = bfdh_RG(10, input);
 * }
**/
template<Order order = height>
tuple<int32_t, RecVec> bfdh_RG(int32_t width, const RecList &rectangles) {
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
        auto best = -1;
        auto best_rot = -1;
        for(auto j = 0; j < HL.size(); ++j) {
            if(HL[j] >= remain[i][1] && width - WL[j] >= remain[i][0]) {
                if(best == -1 || WL[j] > WL[best])
                    best = j;
            }
        }
        if(best > -1) {
            result.push_back(Rectangle{
                WL[best], YL[best], remain[i][0], remain[i][1]});
            HL[best] = remain[i][1];
            WL[best] += remain[i][0];
        }else {
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


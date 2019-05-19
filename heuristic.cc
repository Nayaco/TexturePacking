#ifndef PH_RG
#define PH_RG 1

#include "rectangleVec.hpp"
#include <cstdlib>
using namespace std;

inline int32_t pop(vector<int32_t>&);

inline void remove(vector<int32_t>&, int32_t);

int32_t recursive_update(vector<int32_t>&, int32_t);

void packing(int32_t, int32_t, int32_t, int32_t, 
            const RecList&, 
            vector<int32_t>&, 
            vector<int32_t>&, 
            vector<int32_t>&, 
            vector<int32_t>&, 
            vector<int32_t>&);

template<Order order = width>
tuple<int32_t, RecVec> ph(int32_t width, const RecList& rectangles) {
    int32_t ceilL = 0;
    
    int32_t sortOrder = (uint32_t)order;
    
    vector<int32_t> resultX(rectangles.size());
    vector<int32_t> resultY(rectangles.size());
    vector<int32_t> resultW(rectangles.size());
    vector<int32_t> resultH(rectangles.size());
    RecVec result { };

    RecList remain { rectangles };
    
    for(auto i = 0; i < remain.size(); ++i)
        if(remain[i][0] > remain[i][1])
            remain[i] = ~remain[i];
            
    auto sortedIndices = sort_indexes<RecTuple, RecLess<order>>(remain);
    for(auto i: sortedIndices)
        cout<<' '<<remain[i][0]<<' '<<remain[i][1]<<endl;
    int32_t  x, y, w, h, H;
    x = y = w = h = H = 0;

    while(1) {
        auto idx = pop(sortedIndices);
        if(idx < 0) break;
        auto r = remain[idx];
        if(r[1] > width) {
            resultX[idx] = x;
            resultY[idx] = y;
            resultW[idx] = r[0];
            resultH[idx] = r[1];
            x = r[0], y = H, w = width - r[0], h = r[1], H = H + r[1];
        } else {
            resultX[idx] = x;
            resultY[idx] = y;
            resultW[idx] = r[1];
            resultH[idx] = r[0];
            x = r[1], y = H, w = width - r[1], h = r[0], H = H + r[0];
        }
        packing(x, y ,w ,h, 
                remain, 
                sortedIndices, 
                resultX, 
                resultY, 
                resultW, 
                resultH);
        x = 0, y = H;
    }

    ceilL = H;
    for(auto i = 0; i < rectangles.size(); ++i)
        result.push_back(Rectangle{
            resultX[i], 
            resultY[i],
            resultW[i],
            resultH[i]
            });
    return make_tuple(ceilL, result);
}

void packing(int32_t x, int32_t y, int32_t w, int32_t h, 
            const RecList& remain, 
            vector<int32_t>& indices, 
            vector<int32_t>& resultX, 
            vector<int32_t>& resultY, 
            vector<int32_t>& resultW, 
            vector<int32_t>& resultH) {
    int32_t priority = 6;
    int32_t rotation = 0;
    int32_t best = -1;
    int32_t best_index = -1;
    for(int32_t i = 0; i < indices.size(); i++) {
        int32_t idx = indices[i];
        if(idx >= 0){
            for(int32_t rot = 0; rot < 2; ++rot) {
                if(priority > 1 && remain[idx][rot & 1] == w && remain[idx][rot ^ 1] == h)
                    priority = 1, rotation = rot, best = idx, best_index = i;
                else if(priority > 2 && remain[idx][rot & 1] == w && remain[idx][rot ^ 1] < h)
                    priority = 2, rotation = rot, best = idx, best_index = i;
                else if(priority > 3 && remain[idx][rot & 1] < w && remain[idx][rot ^ 1] == h)
                    priority = 3, rotation = rot, best = idx, best_index = i;
                else if(priority > 4 && remain[idx][rot & 1] < w && remain[idx][rot ^ 1] < h)
                    priority = 4, rotation = rot, best = idx, best_index = i;
                else if(priority > 5)
                    priority = 5, rotation = rot, best = idx, best_index = i;
            }
        }
    }
    
    if(priority < 5) {
        int32_t WW = rotation == 0 ? remain[best][0] : remain[best][1];
        int32_t HH = rotation == 0 ? remain[best][1] : remain[best][0];
        resultX[best] = x;
        resultY[best] = y;
        resultW[best] = WW;
        resultH[best] = HH;
        remove(indices, best_index);

        switch (priority)
        {
            case 2: {
                packing(x, y + HH, w, h - HH, 
                    remain, 
                    indices,
                    resultX, 
                    resultY, 
                    resultW, 
                    resultH);
                break;
            }
            case 3: {
                packing(x + WW, y, w - WW, h, 
                    remain, 
                    indices,
                    resultX, 
                    resultY, 
                    resultW, 
                    resultH);
                break;
            }
            case 4: {
                int32_t min_size = INF;
                for(int32_t idx: indices)
                    if(idx >= 0)
                        min_size = min(min(remain[idx][0], remain[idx][1]), min_size);
                if(w - WW < min_size){
                    packing(x, y + HH, w, h - HH, 
                    remain, 
                    indices,
                    resultX, 
                    resultY, 
                    resultW, 
                    resultH);
                } else if(h - HH < min_size) {
                    packing(x + WW, y, w - WW, h, 
                    remain, 
                    indices,
                    resultX, 
                    resultY, 
                    resultW, 
                    resultH);
                } else if(WW < min_size) {
                    packing(x + WW, y, w - WW, HH, 
                    remain,
                    indices,
                    resultX,
                    resultY,
                    resultW,
                    resultH);
                    packing(x, y + HH, w, h - HH, 
                    remain, 
                    indices,
                    resultX, 
                    resultY, 
                    resultW, 
                    resultH);
                }else {
                    packing(x, y + HH, WW, h - HH, 
                    remain, 
                    indices,
                    resultX, 
                    resultY, 
                    resultW, 
                    resultH);
                    packing(x + WW, y, w - WW, h, 
                    remain,
                    indices,
                    resultX,
                    resultY,
                    resultW,
                    resultH);
                }
                break;
            }
            default:
                break;
        }
    }
}

inline int32_t pop(vector<int32_t>& vec) {
    int32_t result = -1;
    for(auto i = 0; i < vec.size() ; i = -vec[i]) {
        if(vec[i] >= 0) {
            result = vec[i];
            vec[i] = -i - 1;
            recursive_update(vec, i);
            break;
        }
        recursive_update(vec, i);
    }
    return result;
}

inline void remove(vector<int32_t>& vec, int32_t idx) {
    if(vec[idx] >= 0 && idx < vec.size()) {
        vec[idx] = - idx - 1;
        recursive_update(vec, idx);
    }
}

int32_t recursive_update(vector<int32_t>& vec, int32_t idx) {
    if(idx >= 0 && idx >= vec.size())return vec.size();
    vec[idx] = vec[idx] >= 0 ? vec[idx]: -recursive_update(vec, -vec[idx]);
    return vec[idx] >= 0 ? idx: -vec[idx]; 
}

#endif
#ifndef __RV__
#define __RV__

#include <vector>
#include <tuple>
#include <cstdint>
#include <numeric>
#include <algorithm>
#include <functional>
enum Order:bool {
    width = false,
    height = true
};
#define INF 0x7fff'ffff;
struct RecTuple {
    int32_t first, second;
    RecTuple(const int32_t lhs, const int32_t rhs): first(lhs), second(rhs) {}
    RecTuple(const RecTuple& rhs): first(rhs.first), second(rhs.second) {}
    int32_t operator [] (const int idx) const{
        if(idx > 1 || idx < 0) throw "Out of range";
        return idx ? second : first;
    }
    RecTuple& operator ~() {
        first ^= second;
        second ^= first;
        first ^= second;
        return *this;
    }
};

template <int wh = 0>
struct RecLess {
    bool operator ()(const RecTuple &lhs, const RecTuple &rhs) const{
        return lhs[wh] > rhs[wh];
    }
};

struct RecList: public std::vector<RecTuple> {
};

struct Rectangle {
    int32_t x, y, w, h;
};

struct RecVec: public std::vector<Rectangle> {
};

template <typename T, typename F = std::less<T>>
std::vector<int32_t> sort_indexes(const std::vector<T> &v) {
    F compare = F();
    std::vector<int32_t> idx(v.size());
    std::iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(),
        [&v, &compare](int32_t i1, int32_t i2) {return compare(v[i1], v[i2]);});

    return idx;
}

#endif
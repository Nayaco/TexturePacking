#ifndef __RV__
#define __RV__

#include <vector>
#include <cstdint>
#include <numeric>
#include <algorithm>

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

template <typename T>
struct Pod {
    T value;
    bool isNull;
    int32_t nextPos;
};

template <typename T>
struct PodVec: public std::vector<Pod<T>> {
    PodVec(const std::vector<T>& rhs) {
        this->clear();
        for(auto value: rhs) 
            this->push_back(Pod<T>{value, false, -1});
    }

    const Pod<T>& top() {
        for(auto i = 0; !(this->empty()) && i < this->size() && i > -1; i = (*this)[i].nextPos){
            if(!(*this)[i].isNull) 
                return (*this)[i];
        }
        return *(new Pod<T>{T{}, true, -1});
    }
    const Pod<T>& pop() {
        for(auto i = 0; !(this->empty()) && i < this->size(); i = (*this)[i].nextPos){
            if(!(*this)[i].isNull) {
                (*this)[i].isNull = true;
                (*this)[i].nextPos = i < this->size() - 1 ? 
                    ((*this)[i + 1].isNull ? (*this)[i + 1].nextPos : i + 1)
                    : -1;
                return (*this)[i];
            }
        }
        return Pod<T>{T{}, true, -1};
    }
    const T& remove(const int idx) {
        if(!(*this)[idx].isNull) {
            (*this)[idx].isNull = true;
            (*this)[idx].nextPos = idx < this->size() - 1 ? (*this)[idx + 1].nextPos : this->size();
            return (*this)[idx].value;
        }
        else {
            return (*this)[idx].value;
        }
    }
};

template <typename T, typename F>
std::vector<int32_t> sort_indexes(const std::vector<T> &v) {
    F compare = F();
    std::vector<int32_t> idx(v.size());
    std::iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(),
        [&v, &compare](int32_t i1, int32_t i2) {return compare(v[i1], v[i2]);});

    return idx;
}

#endif
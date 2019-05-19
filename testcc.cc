#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <functional>
using namespace std;

#include "pheuristic.cc"
#include "ffdh.cc"
#include "nfdh.cc"
#include "bfdh.cc"

int main(int argc, char const *argv[])
{   
    int32_t wlimit = 30;
    vector<ofstream> files { };
    vector<function<tuple<int32_t, RecVec>(int32_t, const RecList&)>> functions { }; 
    
    RecList list{};
    list.push_back(RecTuple{5,  3});
    list.push_back(RecTuple{5,  3});
    list.push_back(RecTuple{2,  4});
    list.push_back(RecTuple{30, 8});
    list.push_back(RecTuple{10, 20});
    list.push_back(RecTuple{20, 10});
    list.push_back(RecTuple{5,  5});
    list.push_back(RecTuple{5,  5});
    list.push_back(RecTuple{10, 10});
    list.push_back(RecTuple{10, 5});
    list.push_back(RecTuple{6,  4});
    list.push_back(RecTuple{1,  10});
    list.push_back(RecTuple{8,  4});
    list.push_back(RecTuple{6,  6});
    list.push_back(RecTuple{20, 14});

    functions.push_back(function(ph<width>));
    files.push_back(ofstream("ph.out", ios::out));
    functions.push_back(function(ffdh_OG));
    files.push_back(ofstream("ffog.out", ios::out));
    functions.push_back(function(ffdh_RG<width>));
    files.push_back(ofstream("ffrg.out", ios::out));
    functions.push_back(function(nfdh_OG));
    files.push_back(ofstream("nfog.out", ios::out));
    functions.push_back(function(nfdh_RG<width>));
    files.push_back(ofstream("nfrg.out", ios::out));
    functions.push_back(function(bfdh_OG));
    files.push_back(ofstream("bfog.out", ios::out));
    functions.push_back(function(bfdh_RG<width>));
    files.push_back(ofstream("bfrg.out", ios::out));
 
    for(auto idx = 0; idx < functions.size(); ++idx) {
        ofstream &ofs = files[idx];
        int32_t ceilL = 0;
        RecVec  ans { };
        std::tie(ceilL, ans) = functions[idx](wlimit, list);
        ofs<<ceilL<<' '<<wlimit<<endl;
        for(auto i: ans) {
            ofs<<i.x<<' '<<i.y<<' '<<i.w<<' '<<i.h<<endl;
            cout<<"X:"<<i.x<<" ";
            cout<<"Y:"<<i.y<<" "; 
            cout<<"W:"<<i.w<<" ";
            cout<<"H:"<<i.h<<" "<<endl;
        }
        ofs.close();
    }

    return 0;
}

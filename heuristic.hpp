#ifndef __PH__
#define __PH__
#include "rectangleVec.hpp";

enum Order:bool {
    width = false,
    height = true
};

RecVec& ph(uint32_t width, const RecList& rectangles, Order order);

#endif
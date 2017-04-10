#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>
#include <sstream>

template<class T>
std::string toString(T v)
{
    std::stringstream ss;
    ss << v;
    return ss.str();
}

#endif

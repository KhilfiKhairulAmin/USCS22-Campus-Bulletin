#ifndef UTILITY_H
#define UTILITY_H
#include <string>
#include <algorithm>
using namespace std;

string toLowerCase(const string& str)
{
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

#endif
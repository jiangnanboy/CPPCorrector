
#include <string>
//Created by sy on 2023/12/11 22:29.

#ifndef CPPCORRECTOR_MAYBEERR_H
#define CPPCORRECTOR_MAYBEERR_H

using namespace std;

class MayBeErr {
public:
    MayBeErr();
    MayBeErr(string token, int beginIdx, int endIdx, string errInfo);
    ~MayBeErr();

public:
    string token;
    int beginIdx;
    int endIdx;
    string errInfo;
};


#endif //CPPCORRECTOR_MAYBEERR_H

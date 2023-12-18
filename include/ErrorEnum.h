
//Created by sy on 2023/12/11 22:29.
#include <string>
#include <map>


#ifndef CPPCORRECTOR_ERRORENUM_H
#define CPPCORRECTOR_ERRORENUM_H

using namespace std;
class ErrorEnum {
public:
    ErrorEnum();
    ~ErrorEnum();

public:
//    enum ErrorTypeEnum{CONFUSION, WORD, CHR};
    map<int, string> errorTypeEnumCategory;
};


#endif //CPPCORRECTOR_ERRORENUM_H

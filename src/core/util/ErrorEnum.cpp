
//Created by sy on 2023/12/11 22:29.



#include "../../../include/ErrorEnum.h"

ErrorEnum::ErrorEnum() {
    this->errorTypeEnumCategory.insert(pair<int, string>(0, "confusion"));
    this->errorTypeEnumCategory.insert(pair<int, string>(1, "word"));
    this->errorTypeEnumCategory.insert(pair<int, string>(2, "char"));
}
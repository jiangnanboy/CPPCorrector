//Created by sy on 2023/12/11 22:29.



#include "../../../include/MayBeErr.h"

MayBeErr::MayBeErr(string token, int beginIdx, int endIdx, string errInfo) {
    this->token = token;
    this->beginIdx = beginIdx;
    this->endIdx = endIdx;
    this->errInfo = errInfo;
}

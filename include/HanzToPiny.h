
//Created by sy on 2023/12/12 22:29.
#include <string>
#include <set>
#include <list>
#include <lib/self/libhanz2piny/Hanz2Piny.h>
#include <iostream>

#ifndef CPPCORRECTOR_HANZTOPINY_H
#define CPPCORRECTOR_HANZTOPINY_H

using namespace std;

class HanzToPiny {
public:
    HanzToPiny();
    HanzToPiny(Hanz2Piny hanz2Piny);
    ~HanzToPiny();
    string pinyin(string chr);

public:
    const Hanz2Piny hanz2piny;
};


#endif //CPPCORRECTOR_HANZTOPINY_H

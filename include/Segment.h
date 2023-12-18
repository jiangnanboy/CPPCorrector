
//Created by sy on 2023/12/6 22:29.

#include "cppjieba/Jieba.hpp"
#include "Entry.h"
#include <string>
#include <list>
#include <regex>
using namespace std;

#ifndef CPPCORRECTOR_SEGMENT_H
#define CPPCORRECTOR_SEGMENT_H

class Segment {
public:
    Segment();
    Segment(cppjieba::Jieba);
    ~Segment(){};
    Segment(string DICT_PATH, string HMM_PATH, string USER_DICT_PATH, string IDF_PATH, string STOP_WORD_PATH);
    list<Entry> segment(string text);
    list<Entry> segment(string text, bool posi);
    void addDict(string word, int freq, string tag);
    void addDict(string word);
    list<string> splitSentencen(string text);

private:
    cppjieba::Jieba jieba;
};


#endif //CPPCORRECTOR_SEGMENT_H

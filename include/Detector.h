
//Created by sy on 2023/12/11 22:29.
#include <include/NumCpp/NdArray.hpp>
#include "Tokenizer.h"
#include "MayBeErr.h"
#include "LoadDetectorDict.h"
#include "ErrorEnum.h"
#include "../../../NumCpp/include/NumCpp.hpp"

#ifndef CPPCORRECTOR_DETECTOR_H
#define CPPCORRECTOR_DETECTOR_H


class Detector {
public:
    Detector();
    ~Detector();
    void initDetector();
    void enableCharError(bool isCharErrorDetect);
    void enableWordError(bool isWordErrorDetect);
    double ngramScore(list<string> wordList);
    double pplScore(list<string> wordList);
    int wordFrequency(string word);
    void setWordFrequency(string word, int freq);
    bool isFilterToken(string token);
    list<list<MayBeErr>> detect(string text);
    list<list<MayBeErr>> detectShort(string sent, int startIdx);

public:
    Tokenizer tokenizer;
    LoadDetectorDict loadDetectorDict;
    // llm model;
    bool isCharErrorDetect = true;
    bool isWordErrorDetect = true;
    bool initializedDetector = false;
    ErrorEnum errorEnum;
private:
    bool checkContainError(list<MayBeErr> mayBeErr, list<list<MayBeErr>> mayBeErrors);
    void addMayBeErrorItem(list<MayBeErr> mayBeErr, list<list<MayBeErr>> mayBeErrors);
    list<int> getMaybeErrorIndex(nc::NdArray<double> scores, double ratio, int threshold);
    list<int> getMaybeErrorIndexByStddev(nc::NdArray<double > scores);
    list<int> getMaybeErrorIndexByStddev(nc::NdArray<double> scores, int n);
};

#endif //CPPCORRECTOR_DETECTOR_H
















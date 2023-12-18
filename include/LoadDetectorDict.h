
//Created by sy on 2023/12/7 22:29.
#include <string>
#include <map>
#include <fstream>


#ifndef CPPCORRECTOR_LOADDETECTORDICT_H
#define CPPCORRECTOR_LOADDETECTORDICT_H

using namespace std;

class LoadDetectorDict {
public:
    LoadDetectorDict();
    ~LoadDetectorDict();
    void initDetectorDict();
    void initDetectorDict(const string wordFreqPath, const string customConfusionPath, const string customWordFrqPath,
                          const string personNamePath, const string placeNamePath, const string stopwordsPath);
    map<string, int> loadWordFreqDict(string filePath);
    map<string, string> getCustomConfusionDict(string filePath);
    void setCustomConfusionDict(string filePath);

public:
    map<string, int> wordFreq;
    map<string, string> customConfusion;
    map<string, int> customWordFreq;
    map<string, int> personNames;
    map<string, int> placeNames;
    map<string, int> stopWords;
};


#endif //CPPCORRECTOR_LOADDETECTORDICT_H



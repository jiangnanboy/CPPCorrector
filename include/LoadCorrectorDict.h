
//Created by sy on 2023/12/7 22:29.
#include <string>
#include <map>
#include <set>
#include <list>
#include <fstream>


#ifndef CPPCORRECTOR_LOADCORRECTORDICT_H
#define CPPCORRECTOR_LOADCORRECTORDICT_H

using namespace std;

class LoadCorrectorDict {
public:
    LoadCorrectorDict();
    ~LoadCorrectorDict();
    void initCorrectorDict();
    void initCorrectorDict(const string commonCharPath, const string samePinYinPath, const string sameStrokePath);
    set<string> loadSetFile(string filePath);
    map<string, set<string>> loadSamePinYin(string filePath);
    map<string, set<string>> loadSamePinYin(string filePath, string sep);
    map<string, set<string>> loadSameStroke(string filePath);
    map<string, set<string>> loadSameStroke(string filePath, string sep);

public:
    set<string> cnCharSet;
    map<string, set<string>> samePinYin;
    map<string, set<string>> sameStroke;
};


#endif //CPPCORRECTOR_LOADCORRECTORDICT_H


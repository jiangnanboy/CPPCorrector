//Created by sy on 2023/12/6 22:29.

#include "../../include/Segment.h"
#include "../../include/init.h"
#include "../../include/util.h"

Segment::Segment(cppjieba::Jieba jieba):jieba(jieba) {
}

Segment::Segment(string DICT_PATH, string HMM_PATH, string USER_DICT_PATH,
                 string IDF_PATH, string STOP_WORD_PATH):jieba(initJieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH)) {
}

list<Entry> Segment::segment(string text) {
    return this->segment(text, true);
}

list<Entry> Segment::segment(string text, bool posi) {
    list<Entry> entryList;
    vector<pair<string, string> > cutResult;
    jieba.Tag(text, cutResult);
    if(!cutResult.empty()) {
        vector<pair<string, string>> :: iterator iter;
        if(posi) {
            int position = 0;
            Entry entry(cutResult[0].first, cutResult[0].second, position);
            entryList.push_back(entry);
            for(int i=1; i<cutResult.size(); i++) {
                // 中华人民共和国 万岁 ， 中国
                pair<string, string> pairValue = cutResult[i];
                position += cutResult[i - 1].first.length();
                Entry otherEntry(pairValue.first, pairValue.second, position);
                entryList.push_back(otherEntry);
            }
        } else {
            for(iter=cutResult.begin(); iter != cutResult.end(); iter++) {
                Entry entry(iter->first, iter->second);
                entryList.push_back(entry);
            }
        }
    }
    return entryList;
}


void Segment::addDict(string word) {
    this -> jieba.InsertUserWord(word);
}

void Segment::addDict(string word, int freq, string tag) {
    this -> jieba.InsertUserWord(word, freq, tag);
}

list<string> Segment::splitSentencen(string text) {
    vector<string> result = splitEachChar(text);
    string eastr = "";
    list<string> sentenceList;
    for(vector<string>::iterator it=result.begin(); it !=result.end();it++) {
        eastr += *it;
        if(*it == "，") {
            sentenceList.push_back(eastr);
            eastr = "";
        } else if(*it == "。") {
            sentenceList.push_back(eastr);
            eastr = "";
        } else if(*it == "！") {
            sentenceList.push_back(eastr);
            eastr = "";
        } else if(*it == "、") {
            sentenceList.push_back(eastr);
            eastr = "";
        } else if(*it == "？") {
            sentenceList.push_back(eastr);
            eastr = "";
        } else if(*it == "；") {
            sentenceList.push_back(eastr);
            eastr = "";
        } else if(*it == "：") {
            sentenceList.push_back(eastr);
            eastr = "";
        }
    }
    if(!eastr.empty()) {
        sentenceList.push_back(eastr);
    }
    return sentenceList;
}

















//Created by sy on 2023/12/11 22:29.

#include "../../../include/Detector.h"
#include "../../../include/util.h"
#include "../../../include/PropertiesParser.h"
#include <algorithm>
using namespace cppproperties;
using namespace std;

static Properties props = PropertiesParser::Read("../properties.properties");

Detector::Detector() {
    if(!this->initializedDetector) {
        this->initDetector();
    }
}

void Detector::initDetector() {
    clog << "init detector...";
    this->loadDetectorDict.initDetectorDict();
    string DICT_PATH = props.GetProperty("DICT_PATH");
    string HMM_PATH = props.GetProperty("HMM_PATH");
    string USER_DICT_PATH = props.GetProperty("USER_DICT_PATH");
    string IDF_PATH = props.GetProperty("IDF_PATH");
    string STOP_WORD_PATH = props.GetProperty("STOP_WORD_PATH");
    Segment segment(DICT_PATH, HMM_PATH,USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH);
    this->tokenizer.initTokenizer(segment, props.GetProperty("word_freq_path"), this->loadDetectorDict.customWordFreq, this->loadDetectorDict.customConfusion);
    // load llm model
    this->initializedDetector = true;
}

void Detector::enableCharError(bool isCharErrorDetect) {
    this->isCharErrorDetect = isCharErrorDetect;
}

void Detector::enableWordError(bool isWordErrorDetect) {
    this->isWordErrorDetect = isWordErrorDetect;
}

/**
 * language model score
 * @param wordList
 * @return
 */
double Detector::ngramScore(list<string> wordList) {

}

/**
 * perplexity score
 * @param wordList
 * @return
 */
double Detector::pplScore(list<string> wordList) {

}

/**
 * get frequency from wordfreq dict
 * @param word
 * @return
 */
int Detector::wordFrequency(string word) {
    auto iter = this->loadDetectorDict.wordFreq.find(word);
    if(iter != this->loadDetectorDict.wordFreq.end()) {
        return iter->second;
    } else {
        return 0;
    }
}

/**
 * update frequency
 * @param word
 * @param freq
 */
void Detector::setWordFrequency(string word, int freq) {
    this->loadDetectorDict.wordFreq.insert(pair<string, int>(word, freq));
}

/**
 * filter the token?
 * @param token
 * @return
 */
bool Detector::isFilterToken(string token) {
    bool flag = false;
    if(isBlank(token)) {
        flag = true;
    } else if(isNumber(token)) {
        flag = true;
    } else if (isEnglish(token)) {
        flag = true;
    } else if(!isChinese(token)) {
        flag = true;
    }
    return flag;
}

/**
 * text detection
 * @param text
 * @return
 */
list<list<MayBeErr>> Detector::detect(string text) {
    list<list<MayBeErr>> mayBeErrors;
    if(isBlank(trim(text))) {
        return mayBeErrors;
    }
    list<string> splitSentList = this->tokenizer.split2ShortSent(text);
    int startIdx = 0;
    for(string sent : splitSentList) {
        list<list<MayBeErr>> resultErrorList = this->detectShort(sent, startIdx);
        mayBeErrors.insert(mayBeErrors.end(), resultErrorList.begin(), resultErrorList.end());
        startIdx += sent.length();
    }
    return mayBeErrors;
}

list<list<MayBeErr>> Detector::detectShort(string sent, int startIdx) {
    list<list<MayBeErr>> maybeErrors;
    map<string, string>::iterator iter = this -> loadDetectorDict.customConfusion.begin();
    while(iter != this->loadDetectorDict.customConfusion.end()) {
        int idx = sent.find(iter->first);
        if(idx != string::npos) {
            list<MayBeErr> mayBeErrList;
            MayBeErr mayBeErr(iter->first, idx+startIdx, idx+iter->first.length()+startIdx, this->errorEnum.errorTypeEnumCategory[0]);
            mayBeErrList.push_back(mayBeErr);
            this->addMayBeErrorItem(mayBeErrList, maybeErrors);
        }
    }
    if(this->isWordErrorDetect) {
        //segment
        list<Entry> tokens = this->tokenizer.tokenizer(sent);
        //unregistered words are added to the suspected error dictionary
        for(list<Entry>::iterator it=tokens.begin(); it!=tokens.end(); it++) {
            string word = it->getWord();
            if(this->isFilterToken(word)) {
                continue;
            }
            if(this->loadDetectorDict.wordFreq.find(word) != this->loadDetectorDict.wordFreq.end()) {
                continue;
            }
            int beginIdx = it->getOffset();
            int endIdx = beginIdx + word.length();
            list<MayBeErr> mayBeErrList;
            MayBeErr mayBeErr(word, beginIdx + startIdx, endIdx + startIdx, this->errorEnum.errorTypeEnumCategory[1]);
            mayBeErrList.push_back(mayBeErr);
            this->addMayBeErrorItem(mayBeErrList, maybeErrors);
        }
    }

    // the language model detects suspected error words
    if(this->isCharErrorDetect) {
        list<list<double>> ngramAvgSAcores;
        list<int> ngramNum = {2,3};
        for(list<int>::iterator it=ngramNum.begin(); it!=ngramNum.end(); it++) {
            list<double> scores;
            for(int i=0; i<(sent.length() - *it + 1); i++) {
                sent.substr(i, i + *it);
                /**
                 * to do...
                 *
                 *
                 *
                 *
                 *
                 */
            }
        }
    }

}

/**
 * check the error set contains the error location?
 * @param mayBeErr [ErrorWord, beginPos, endPos, errorType]
 * @param mayBeErrors list
 * @return
 */
bool Detector::checkContainError(list<MayBeErr> mayBeErr, list<list<MayBeErr>> mayBeErrors) {
    for(list<list<MayBeErr>> :: iterator it=mayBeErrors.begin(); it!=mayBeErrors.end(); it++) {
        for(list<MayBeErr>::iterator it1=(*it).begin(); it1!=(*it).end(); it1++) {
            MayBeErr mayBeErr1 = *it1;
            for(list<MayBeErr> ::iterator it2=mayBeErr.begin(); it2!=mayBeErr.end(); it2++) {
                MayBeErr mayBeErr2 = *it2;
                if((mayBeErr1.token==mayBeErr2.token) && (mayBeErr2.beginIdx >= mayBeErr1.beginIdx) && (mayBeErr2.endIdx <= mayBeErr1.endIdx)) {
                    return true;
                }
            }
        }
        return false;
    }
}

void Detector::addMayBeErrorItem(list<MayBeErr> mayBeErr, list<list<MayBeErr>> mayBeErrors) {
    if(!(find(mayBeErrors.begin(), mayBeErrors.end(), mayBeErr) != mayBeErrors.end()) && (!this->checkContainError(mayBeErr, mayBeErrors))) {
        mayBeErrors.push_back(mayBeErr);
    }
}

list<int> Detector::getMaybeErrorIndex(nc::NdArray<double> scores, double ratio, int threshold) {

}

list<int> Detector::getMaybeErrorIndexByStddev(nc::NdArray<double > scores) {

}

list<int> Detector::getMaybeErrorIndexByStddev(nc::NdArray<double> scores, int n) {

}
















//Created by sy on 2023/12/8 22:29.
#include <filesystem>
#include <iostream>
#include <fstream>
#include "../../../include/Tokenizer.h"
#include "../../../include/util.h"


void Tokenizer::initTokenizer(Segment seg, const string wordFreqPath, map<string, int> customWordFreq, map<string, string> customConfusion) {
    this -> seg = seg;
    this -> addCustomDictionary(wordFreqPath, customWordFreq, customConfusion);
}

/**
 * add custom dictionary to jieba
 * @param wordFreqPath
 * @param customWordFreq
 * @param customConfusion
 */
void Tokenizer::addCustomDictionary(const string wordFreqPath, map<string, int> customWordFreq, map<string, string> customConfusion) {
    if(!filesystem::exists(wordFreqPath)) {
        cerr << "Error: File path is empty!" << endl;
    } else {
        ifstream infile(wordFreqPath);
        if(infile.good()) {
            string line;
            while(getline(infile, line)) {
                line = trim(line);
                vector<string> wordInfo = stringSplit(line, " ");
                this -> seg.addDict(wordInfo[0], stoi(wordInfo[1]), wordInfo[2]);
            }
            infile.close();
        }
        for(map<string, int>::iterator it=customWordFreq.begin(); it!=customWordFreq.end(); it++) {
            this -> seg.addDict(it -> first);
        }
        for(map<string, string>::iterator it=customConfusion.begin(); it!=customConfusion.end(); it++) {
            this -> seg.addDict(it -> first);
            this -> seg.addDict(it -> second);
        }
    }
}

list<Entry> Tokenizer::tokenize(string text) {
    return this->tokenize(text, true);
}

list<Entry> Tokenizer::tokenize(string text, bool posi) {
    return this->seg.segment(text, posi);
}

list<string> Tokenizer::split2ShortSent(string text) {
    return this->seg.splitSentencen(text);
}

list<string> Tokenizer::whiteSpaceTokenizer(string text) {
    vector<string> eachToken = splitEachChar(text);
    return list<string>(eachToken.begin(), eachToken.end());
}

list<Entry> Tokenizer::tokenizer(string text) {
    return this->tokenize(text, true);
}

list<list<string>> Tokenizer::cutSentence(string sentence) {
    return this->cutSentence(sentence, "word", false);
}

list<list<string>> Tokenizer::cutSentence(string sentence, string cutType) {
    return this->cutSentence(sentence, cutType, false);
}

/**
 * cut sentence
 * @param sentence
 * @param cutType
 * @param pos
 * @return
 */
list<list<string>> Tokenizer::cutSentence(string sentence, string cutType, bool pos) {
    list<list<string>> wordPosList;
    list<string> wordList;
    list<string> posList;
    if(pos) {
        if("word" == cutType) {
            list<Entry> entryList = this->tokenizer(sentence);
            for(list<Entry>::iterator it=entryList.begin(); it!=entryList.end(); it++) {
                wordList.push_back(it->getWord());
                posList.push_back(it->getPos());
            }
        } else if("char" == cutType) {
            wordList = this->whiteSpaceTokenizer(sentence);
            for(list<string>::iterator it=wordList.begin(); it!=wordList.end(); it++) {
                list<Entry> entry = this->tokenizer(*it);
                for(list<Entry>::iterator it=entry.begin();it!= entry.end();it++) {
                    posList.push_back(it->getPos());
                }
            }
        }
        wordPosList.push_back(wordList);
        wordPosList.push_back(posList);
    } else {
        if("word" == cutType) {
            list<Entry> entryList = this->tokenizer(sentence);
            for(list<Entry>::iterator it=entryList.begin(); it!=entryList.end(); it++) {
                wordList.push_back(it->getWord());
            }
        } else if("char" == cutType) {
            wordList = this->whiteSpaceTokenizer(sentence);
        }
        wordPosList.push_back(wordList);
        wordPosList.push_back(posList);
    }
    return wordPosList;
}


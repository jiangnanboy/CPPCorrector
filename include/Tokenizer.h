
//Created by sy on 2023/12/8 22:29.
#include <string>
#include <map>
#include <vector>
#include <list>
#include "Entry.h"
#include "Segment.h"

#ifndef CPPCORRECTOR_TOKENIZER_H
#define CPPCORRECTOR_TOKENIZER_H

using namespace std;

class Tokenizer {
public:
    Tokenizer();
    ~Tokenizer();
    void initTokenizer(Segment seg, const string wordFreqPath, map<string, int> customWordFreq, map<string, string> customConfusion);
    void addCustomDictionary(const string wordFreqPath, map<string, int> customWordFreq, map<string, string> customConfusion);
    list<Entry> tokenize(string text, bool posi);
    list<Entry> tokenize(string text);
    list<string> split2ShortSent(string text);
    list<string> whiteSpaceTokenizer(string text);
    list<Entry> tokenizer(string text);
    list<list<string>> cutSentence(string sentence);
    list<list<string>> cutSentence(string sentence, string cutType);
    list<list<string>> cutSentence(string sentence, string cutType, bool pos);

public:
    Segment seg;
};


#endif //CPPCORRECTOR_TOKENIZER_H


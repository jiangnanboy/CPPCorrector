
//Created by sy on 2023/12/11 22:29.
#include "HanzToPiny.h"


#ifndef CPPCORRECTOR_CORRECTOR_H
#define CPPCORRECTOR_CORRECTOR_H


class Corrector {
public:
    Corrector();
    ~Corrector();
    void initCorrector();
    void initPinYin();
    set<string> getSamePinYin(string chr);
    set<string> getSameStroke(string chr);
    set<string> known(set<string>);
    set<string> confusionCustomSet(string word);
    list<string> generateItems(string word);
    list<string> generateItems(string word, int fragment);
    list<string> getLmCorrectItem(string curItem, list<string> candidatesList, string beforeSent, string afterSent);
    list<string> getLmCorrectItem(string curItem, list<string> candidatesList, string beforeSent, string afterSent, int threshold);
    list<string> getLmCorrectItem(string curItem, list<string> candidatesList, string beforeSent, string afterSent, int threshold, string cutType);
    string correct(string text);
    string correct(string text, int numFragment, int threshold);

private:
    set<string> confusionCharSet(string chr);
    set<string> confusionWordSet(string word);

public:
    bool initializedCorrector= false;
    HanzToPiny hanzToPiny;
};


#endif //CPPCORRECTOR_CORRECTOR_H

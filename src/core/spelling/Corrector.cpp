
//Created by sy on 2023/12/11 22:29.



#include "../../../include/Corrector.h"


Corrector::Corrector() {

}

void Corrector::initCorrector() {

}

void Corrector::initPinYin() {

}

set<string> Corrector::getSamePinYin(string chr) {

}

set<string> Corrector::getSameStroke(string chr) {

}

set<string> Corrector::known(set<string>) {

}

set<string> Corrector::confusionCustomSet(string word) {

}

list<string> Corrector::generateItems(string word) {

}

list<string> Corrector::generateItems(string word, int fragment) {

}

list<string> Corrector::getLmCorrectItem(string curItem, list<string> candidatesList, string beforeSent, string afterSent) {

}

list<string> Corrector::getLmCorrectItem(string curItem, list<string> candidatesList, string beforeSent, string afterSent, int threshold) {

}

list<string> Corrector::getLmCorrectItem(string curItem, list<string> candidatesList, string beforeSent, string afterSent, int threshold, string cutType) {

}

string Corrector::correct(string text) {

}

string Corrector::correct(string text, int numFragment, int threshold) {

}



set<string> Corrector::confusionCharSet(string chr) {

}

set<string> Corrector::confusionWordSet(string word) {

}



























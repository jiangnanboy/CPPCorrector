
//Created by sy on 2023/12/12 22:29.


#include "../../../include/SpellingEntry.h"

SpellingEntry::SpellingEntry() {}
SpellingEntry::SpellingEntry(string word, double score) {
    this->word = word;
    this->score = score;
}

void SpellingEntry::setWord(string word) {
    this->word = word;
}

string SpellingEntry::getWord() {
    return this->word;
}

void SpellingEntry::setScore(double score) {
    this->score = score;
}

double SpellingEntry::getScore() {
    return this->score;
}
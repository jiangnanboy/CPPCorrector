
//Created by sy on 2023/12/6 22:29.



#include "../../include/Entry.h"

Entry::Entry(string word, string pos) {
    this->word = word;
    this->pos = pos;
}

Entry::Entry(string word, string pos, int offset) {
    this->word=word;
    this->pos=pos;
    this->offset=offset;
}

void Entry::setWord(string word) {
    this->word = word;
}

string Entry::getWord() {
    return this->word;
}

void Entry::setPos(string pos) {
    this->pos = pos;
}

string Entry::getPos() {
    return this->pos;
}

void Entry::setOffset(int offset) {
    this->offset=offset;
}

int Entry::getOffset() {
    return this->offset;
}
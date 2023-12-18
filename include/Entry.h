
//Created by sy on 2023/12/6 22:29.

#include <string>
using namespace std;

#ifndef CPPCORRECTOR_ENTRY_H
#define CPPCORRECTOR_ENTRY_H


class Entry {
public:
    Entry(string word, string pos);
    Entry(string word, string pos, int offset);
    ~Entry(){};
    string getWord();
    void setWord(string word);
    string getPos();
    void setPos(string pos);
    int getOffset();
    void setOffset(int offset);
private:
    string word;
    string pos;
    int offset;
};


#endif //CPPCORRECTOR_ENTRY_H

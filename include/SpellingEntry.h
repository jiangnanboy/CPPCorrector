
//Created by sy on 2023/12/12 22:29.
#include <string>


#ifndef CPPCORRECTOR_SPELLINGENTRY_H
#define CPPCORRECTOR_SPELLINGENTRY_H

using namespace std;

class SpellingEntry {
public:
    SpellingEntry();
    SpellingEntry(string word, double score);
    ~SpellingEntry();
    void setWord(string word);
    string getWord();
    void setScore(double score);
    double getScore();
private:
    string word;
    double score;
};


#endif //CPPCORRECTOR_SPELLINGENTRY_H

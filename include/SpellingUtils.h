
//Created by sy on 2023/12/12 22:29.
#include <set>
#include <string>
#include <list>

#ifndef CPPCORRECTOR_SPELLINGUTILS_H
#define CPPCORRECTOR_SPELLINGUTILS_H

using namespace std;

class SpellingUtils {
public:
    SpellingUtils();
    ~SpellingUtils();
    set<string> editDisWord(string word, set<string> charSet);
};


#endif //CPPCORRECTOR_SPELLINGUTILS_H

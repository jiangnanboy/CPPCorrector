
//Created by sy on 2023/12/12 22:29.


#include "../../../include/util.h"
#include "../../../include/SpellingUtils.h"

/**
 * all edits that are one edit away from 'word'
 * @param word
 * @param charSet
 * @return
 */
set<string> SpellingUtils::editDisWord(string word, set<string> charSet) {
    // splits = [(word[:i], word[i:]) for i in range(len(word) + 1)]
    list<string> splitRList;
    vector<string> splitVector = splitEachChar(word);
    for(int i=0; i<splitVector.size(); i++) {
        vector<string> left{&splitVector[0], &splitVector[i]};
        vector<string> right{&splitVector[i+1], &splitVector[splitVector.size()]};
        string leftRight = "";
        for(int l=0; l<left.size(); l++) {
            leftRight += left[i];
        }
        leftRight += ",";
        for(int r=0; r<right.size(); r++) {
            leftRight += right[i];
        }
        splitRList.push_back(leftRight);
    }

    // transposes = [L + R[1] + R[0] + R[2:] for L, R in splits if len(R) > 1]
    list<string> transposesList;
    for(list<string>::iterator it=splitRList.begin(); it!=splitRList.end(); it++) {
        vector<string> strSplit = stringSplit(*it, ",");
        if((strSplit.size() == 2) && (strSplit[1].length() > 1)) {
            vector<string> rightSplit = splitEachChar(strSplit[1]);
            string str = strSplit[0];
            str += rightSplit[1];
            str += rightSplit[0];
            for(int i=2; i<rightSplit.size(); i++) {
                str += rightSplit[i];
            }
            transposesList.push_back(str);
        }
    }

    // replaces = [L + c + R[1:] for L, R in splits if R for c in char_set]
    list<string> replacesList;
    for(list<string>::iterator it=splitRList.begin(); it!=splitRList.end(); it++) {
        vector<string> strSplit = stringSplit(*it, ",");
        if((strSplit.size() == 2) && (strSplit[1].length() >= 1)) {
            vector<string> rightSplit = splitEachChar(strSplit[1]);
            string str = strSplit[0];
            for(string chr:charSet) {
                str += chr;
                for(int i=1; i<rightSplit.size(); i++) {
                    str += rightSplit[i];
                }
                replacesList.push_back(str);
            }
        }
    }

    list<string> editDistList;
    if(!transposesList.empty() && (transposesList.size()>0)) {
        editDistList.insert(editDistList.end(), transposesList.begin(), transposesList.end());
    }

    if(!replacesList.empty() && (replacesList.size()>0)) {
        editDistList.insert(editDistList.end(), replacesList.begin(), replacesList.end());
    }

    return set<string>(editDistList.begin(), editDistList.end());
}



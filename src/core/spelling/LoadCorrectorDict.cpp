
//Created by sy on 2023/12/7 22:29.
#include <iostream>
#include <filesystem>
#include "../../../include/util.h"
#include "../../../include/LoadDetectorDict.h"
#include "../../../include/PropertiesParser.h"
#include "../../../include/LoadCorrectorDict.h"

using namespace cppproperties;
using namespace std;

static Properties props = PropertiesParser::Read("../properties.properties");

void LoadCorrectorDict::initCorrectorDict() {
    string commonCharPath = props.GetProperty("common_char_path");
    string samePinYinPath = props.GetProperty("same_pinyin_path");
    string sameStrokePath = props.GetProperty("same_stroke_path");
    this -> initCorrectorDict(commonCharPath, samePinYinPath, sameStrokePath);
}

void LoadCorrectorDict::initCorrectorDict(const string commonCharPath, const string samePinYinPath, const string sameStrokePath) {
    cout << "corrector dict init ...";
    this -> cnCharSet = loadSetFile(commonCharPath);
    this -> samePinYin = loadSamePinYin(samePinYinPath);
    this -> sameStroke = loadSameStroke(sameStrokePath);
}

/**
 * load set file
 * @param filePath
 * @return
 */
set<string> LoadCorrectorDict::loadSetFile(string filePath) {
    set<string> cnCharSet;
    if(!filesystem::exists(filePath)) {
        cerr << "Error: File path is empty!" << endl;
    } else {
        ifstream infile(filePath);
        if(infile.good()) {
            string line;
            while(getline(infile, line)) {
                line = trim(line);
                if(line != "") {
                    if(!startsWith(line, "#")) {
                        cnCharSet.insert(line);
                    }
                }
            }
            infile.close();
        }
    }
    return cnCharSet;
}

map<string, set<string>> LoadCorrectorDict::loadSamePinYin(string filePath) {
    return this -> loadSamePinYin(filePath, "\t");
}

/**
 * load same pinyin
 * @param filePath
 * @param sep
 * @return
 */
map<string, set<string>> LoadCorrectorDict::loadSamePinYin(string filePath, string sep) {
    map<string, set<string>> samePinYin;
    if(!filesystem::exists(filePath)) {
        cerr << "Error: File path is empty!" << endl;
    } else {
        ifstream infile(filePath);
        if(infile.good()) {
            string line;
            while(getline(infile, line)) {
                line = trim(line);
                if(line != "") {
                    if(!startsWith(line, "#")) {
                        vector<string> info = stringSplit(line, sep);
                        if(info.size() > 2) {
                            string keyChar = trim(info[0]);
                            set<string> value;
                            vector<string> samePronSameTone = splitEachChar(info[1]);
                            vector<string> samePronDiffTone = splitEachChar(info[2]);
                            value.insert(samePronSameTone.begin(), samePronSameTone.end());
                            value.insert(samePronDiffTone.begin(), samePronDiffTone.end());
                            if((keyChar != "") && (value.size() > 0)) {
                                samePinYin.insert(pair<string, set<string>>(keyChar, value));
                            }
                        }
                    }
                }
            }
            infile.close();
        }
    }
    return samePinYin;
}

map<string, set<string>> LoadCorrectorDict::loadSameStroke(string filePath) {
    return this -> loadSameStroke(filePath, "\t");
}

/**
 * load same stroke
 * @param filePath
 * @param sep
 * @return
 */
map<string, set<string>> LoadCorrectorDict::loadSameStroke(string filePath, string sep) {
    map<string, set<string>> sameStroke;
    if(!filesystem::exists(filePath)) {
        cerr << "Error: File path is empty!" << endl;
    } else {
        ifstream infile(filePath);
        if(infile.good()) {
            string line;
            while(getline(infile, line)) {
                line = trim(line);
                if(line != "") {
                    if(!startsWith(line, "#")) {
                        vector<string> info = stringSplit(line, sep);
                        if(info.size() > 1) {
                            for(int i=0; i<info.size(); i++) {
                                set<string> exist;
                                if(sameStroke.find(info[i]) != sameStroke.end()) {
                                    exist = sameStroke[info[i]];
                                }
                                vector<string> subInfo1{&info[0], &info[i]};
                                vector<string> subInfo2{&info[i+1], &info[info.size()]};
                                set<string> current;
                                current.insert(subInfo1.begin(), subInfo1.end());
                                current.insert(subInfo2.begin(), subInfo2.end());
                                set<string> value;
                                value.insert(exist.begin(), exist.end());
                                value.insert(current.begin(), current.end());
                                sameStroke.insert(pair<string, set<string>>(info[i], value));
                            }

                        }
                    }
                }
            }
            infile.close();
        }
    }
    return sameStroke;
}



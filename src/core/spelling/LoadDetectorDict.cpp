
//Created by sy on 2023/12/7 22:29.
#include <iostream>
#include <filesystem>
#include "../../../include/util.h"
#include "../../../include/LoadDetectorDict.h"
#include "../../../include/PropertiesParser.h"

using namespace cppproperties;
using namespace std;

static Properties props = PropertiesParser::Read("../properties.properties");

void LoadDetectorDict::initDetectorDict() {
    string wordFreqPath = props.GetProperty("word_freq_path");
    string customConfusionPath = props.GetProperty("custom_confusion_path");
    string customWordFrqPath = props.GetProperty("custom_word_freq_path");
    string personNamePath = props.GetProperty("person_name_path");
    string placeNamePath = props.GetProperty("place_name_path");
    string stopwordsPath = props.GetProperty("stopwords_path");
    this -> initDetectorDict(wordFreqPath, customConfusionPath, customWordFrqPath,
                             personNamePath, placeNamePath, stopwordsPath);
}

void LoadDetectorDict::initDetectorDict(const string wordFreqPath, const string customConfusionPath, const string customWordFrqPath,
                                        const string personNamePath, const string placeNamePath, const string stopwordsPath) {
    cout << "detector dict init ...";
    // word frequenecy dict
    this -> wordFreq = loadWordFreqDict(wordFreqPath);
    // custom confusion dict
    this -> customConfusion = getCustomConfusionDict(customConfusionPath);
    // custom word segmentation dict
    this -> customWordFreq = loadWordFreqDict(customWordFrqPath);
    this -> personNames = loadWordFreqDict(personNamePath);
    this -> placeNames = loadWordFreqDict(placeNamePath);
    this -> stopWords = loadWordFreqDict(stopwordsPath);

    // merge dict
    this -> customWordFreq.insert(this -> personNames.begin(), this -> personNames.end());
    this -> customWordFreq.insert(this -> placeNames.begin(), this -> placeNames.end());
    this -> customWordFreq.insert(this -> stopWords.begin(), this -> stopWords.end());
    this -> wordFreq.insert(this -> customWordFreq.begin(), this -> customWordFreq.end());
}

/**
 * load word freq dict
 * @param filePath
 * @return
 */
map<string, int> LoadDetectorDict::loadWordFreqDict(string filePath) {
    map<string, int> wordFreq;
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
                        vector<string> info = stringSplit(line, " ");
                        if(info.size() >= 1) {
                            string word = info[0];
                            int freq = 1;
                            if(info.size() > 1) {
                                freq = stoi(info[1]);
                            }
                            wordFreq.insert(pair<string, int>(word, freq));
                        }
                    }
                }
            }
            infile.close();
        }
    }
    return wordFreq;
}

/**
 * load custom confusion dict
 * @param filePath
 * @return
 */
map<string, string> LoadDetectorDict::getCustomConfusionDict(string filePath) {
    map<string, string> customConfusion;
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
                        vector<string> info = stringSplit(line, " ");
                        if(info.size() >= 2) {
                            string variant = info[0];
                            string origin = info[1];
                            int freq = 1;
                            if(info.size() > 2) {
                                freq = stoi(info[2]);
                            }
                            this -> wordFreq.insert(pair<string, int>(origin, freq));
                            customConfusion.insert(pair<string, string>(variant, origin));
                        }
                    }
                }
            }
            infile.close();
        }
    }
    return customConfusion;
}

/**
 * set custom confusion dict
 * @param filePath
 */
void LoadDetectorDict::setCustomConfusionDict(string filePath) {
    if(this -> customConfusion.empty()) {
        this -> customConfusion = this -> getCustomConfusionDict(filePath);
    } else {
        map<string, string> customDict = this->getCustomConfusionDict(filePath);
        this -> customConfusion.insert(customDict.begin(), customDict.end());
    }
}


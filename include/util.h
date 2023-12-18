//Created by sy on 2023/12/5 22:29.


#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

string& trim(string& s);

bool startsWith(string s, string sub);

bool endsWith(string s, string sub);

vector<string> stringSplit(const string& str, string delim);

vector <string> splitEachChar(const string chars);

string getString(list<string> sentence);

bool isBlank(string str);

bool isAlpha(string str);

bool isChinese(char c);

bool isChinese(string str);

bool isNumber(string str);

bool isEnglish(string str);

bool isUrl(string str);

bool isMatch(string regex, string str);

bool isSubMatch(string regex, string str);

string half2FullChange(string input);

string full2HalfChange(string input);

string utf8ToUnicode(string str);

























































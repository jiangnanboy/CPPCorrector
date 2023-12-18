//Created by sy on 2023/12/5 22:29.

#include "../../../include/util.h"

string& trim(string& s) {
    if(s.empty()) {
        return s;
    }
    s.erase(0, s.find_first_not_of(" \t\r\n"));
    s.erase(s.find_last_not_of(" \t\r\n") + 1);
    return s;
}

bool startsWith(string s, string sub){
    return s.find(sub)==0? true: false;
}

bool endsWith(string s,string sub){
    return s.rfind(sub)==(s.length()-sub.length())?true:false;
}

vector<string> stringSplit(const string& str, string delim) {
    size_t previous = 0;
    size_t current = str.find(delim);
    vector<string> elems;
    while (current != string::npos) {
        if (current > previous) {
            elems.push_back(str.substr(previous, current - previous));
        }
        previous = current + 1;
        current = str.find(delim, previous);
    }
    if (previous != str.size()) {
        elems.push_back(str.substr(previous));
    }
    return elems;
}

vector <string> splitEachChar(const string chars)
{
    vector<string> words;
    string input(chars);
    int len = input.length();
    int i = 0;
    while (i < len) {
        int next = 1;
        if ((input[i] & 0x80) == 0x00) {
        } else if ((input[i] & 0xE0) == 0xC0) {
            next = 2;
        } else if ((input[i] & 0xF0) == 0xE0) {
            next = 3;
        } else if ((input[i] & 0xF8) == 0xF0) {
            next = 4;
        }
        words.push_back(input.substr(i, next));
        i += next;
    }
    return words;
}

string getString(list<string> sentence) {
    string str = "";
    for(string token : sentence) {
        str += token;
    }
    return str;
}

bool isBlank(string str) {
    return str.empty();
}

bool isAlpha(string str) {

}

bool isChinese(char c) {

}

bool isChinese(string str) {
    bool flag=true;
    int i = 0;
    while (str[i] != 0)
    {
        if (str[i] & 0x80 && str[i] & 0x40 && str[i] & 0x20) {
            int byteCount = 0;
            if (str[i] & 0x10) {
                byteCount = 4;
            } else {
                byteCount = 3;
            }
            for (int a = 0; a < byteCount; a++) {
                i++;
            }
        } else if (str[i] & 0x80 && str[i] & 0x40) {
            i += 2;
            flag = false;
            break;
        } else {
            i += 1;
            flag = false;
            break;
        }
    }
    return flag;
}

bool isNumber(string str) {
    bool flag=true;
    int i = 0;
    while (str[i] != 0)
    {
        if (str[i] & 0x80 && str[i] & 0x40 && str[i] & 0x20) {
            int byteCount = 0;
            if (str[i] & 0x10) {
                byteCount = 4;
            } else {
                byteCount = 3;
            }
            for (int a = 0; a < byteCount; a++) {
                i++;
            }
            flag = false;
            break;
        } else if (str[i] & 0x80 && str[i] & 0x40) {
            i += 2;
            flag = false;
            break;
        } else {
            i += 1;
        }
    }
    return flag;
}

bool isEnglish(string str) {
    bool flag=true;
    int i = 0;
    while (str[i] != 0)
    {
        if (str[i] & 0x80 && str[i] & 0x40 && str[i] & 0x20) {
            int byteCount = 0;
            if (str[i] & 0x10) {
                byteCount = 4;
            } else {
                byteCount = 3;
            }
            for (int a = 0; a < byteCount; a++) {
                i++;
            }
            flag = false;
            break;
        } else if (str[i] & 0x80 && str[i] & 0x40) {
            i += 2;
            flag = false;
            break;
        } else {
            i += 1;
        }
    }
    return flag;
}

bool isUrl(string str) {

}

bool isMatch(string regex, string str) {

}

bool isSubMatch(string regex, string str) {

}

string half2FullChange(string input) {

}

string full2HalfChange(string input) {
    string result = "";
    unsigned char tmp; unsigned char tmp1;
    for (unsigned int i = 0; i < input.length(); i++) {
        tmp = input[i];
        tmp1 = input[i + 1];
        if (tmp == 163) {///第一个字节是163，标志着是全角字符
            result += (unsigned char)input[i + 1] - 128;
            i++;
            continue;
        }
        else if (tmp > 163) {//汉字
            result += input.substr(i, 2);
            i++;
            continue;
        }
        else if (tmp == 161 && tmp1 == 161) {///处理全角空格
            result += "";
            i++;
        }
        else if (tmp == 161 && tmp1 == 171) {///处理全角空格
            result += 126;
            i++;
        }
        else {
            result += input.substr(i, 1);
        }
    }
    return result;
}

string utf8ToUnicode(string str) {
    
}





















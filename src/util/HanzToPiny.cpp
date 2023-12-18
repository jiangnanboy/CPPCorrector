
//Created by sy on 2023/12/12 22:29.



#include "../../include/HanzToPiny.h"
#include "../../include/util.h"

HanzToPiny::HanzToPiny(Hanz2Piny hanz2Piny):hanz2piny(hanz2Piny) {
}

/**
 * hanzi to pinyin
 * @param chr
 * @return
 */
string HanzToPiny::pinyin(string chr) {
    chr = trim(chr);
    vector<pair<bool, vector<string>>> pinyin_list_list = hanz2piny.toPinyinFromUtf8( chr,false,false,"");
    string hanPiny = "";
    for (const auto& e : pinyin_list_list) {
        auto pinyin_list = e.second;
        if (pinyin_list.size() == 1) {          // 单音字
            auto pinyin = pinyin_list[0];
            hanPiny += pinyin;
        } else if (pinyin_list.size() > 1) {    // 多音字
            auto pinyin = pinyin_list[1];
            hanPiny += pinyin;
        } else {                                // 该 UTF-8 编码并无对应汉字，相应也就不存在拼音
            NULL;
        }
    }
    return hanPiny;
}

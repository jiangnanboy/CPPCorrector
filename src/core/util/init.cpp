//Created by sy on 2023/12/5 22:29.
#include "../../../include/init.h"

cppjieba::Jieba initJieba(string DICT_PATH, string HMM_PATH, string USER_DICT_PATH,
                          string IDF_PATH, string STOP_WORD_PATH) {
    std::cout << "init jieba model ... " << std::endl;
    cppjieba::Jieba jieba(DICT_PATH,
                          HMM_PATH,
                          USER_DICT_PATH,
                          IDF_PATH,
                          STOP_WORD_PATH);
    return jieba;
}





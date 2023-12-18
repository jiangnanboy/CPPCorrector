//Created by sy on 2023/12/5 22:29.
#include "cppjieba/Jieba.hpp"
#include <string>
using namespace std;
cppjieba::Jieba initJieba(string DICT_PATH, string HMM_PATH, string USER_DICT_PATH,
                          string IDF_PATH, string STOP_WORD_PATH);
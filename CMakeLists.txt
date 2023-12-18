cmake_minimum_required(VERSION 3.17)
project(CPPCorrector)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(cppjieba-5.0.3)
include_directories(cppjieba-5.0.3/include)
include_directories(cppjieba-5.0.3/deps)

add_subdirectory(hanz2piny)
include_directories(hanz2piny/src)
include_directories(hanz2piny/refer)

include_directories(NumCpp)
include_directories(NumCpp/include)


add_executable(CPPCorrector include/util.h src/core/util/util.cpp include/init.h src/core/util/init.cpp src/util/Entry.cpp include/Entry.h src/util/Segment.cpp include/Segment.h src/core/spelling/LoadDetectorDict.cpp include/LoadDetectorDict.h src/core/spelling/LoadCorrectorDict.cpp include/LoadCorrectorDict.h src/core/spelling/Tokenizer.cpp include/Tokenizer.h src/core/util/ErrorEnum.cpp include/ErrorEnum.h src/core/spelling/Detector.cpp include/Detector.h src/core/spelling/Corrector.cpp include/Corrector.h src/core/spelling/MayBeErr.cpp include/MayBeErr.h src/util/HanzToPiny.cpp include/HanzToPiny.h src/core/spelling/SpellingEntry.cpp include/SpellingEntry.h src/core/spelling/SpellingUtils.cpp include/SpellingUtils.h)


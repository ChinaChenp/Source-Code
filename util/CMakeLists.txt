cmake_minimum_required (VERSION 2.8)

project (basetool)

enable_testing()

set(CXX_FLAGS
    -g
    -D_FILE_OFFSET_BITS=64
    -Wall
    )

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
MESSAGE(STATUS "BINARY dir " ${basetool_BINARY_DIR})
MESSAGE(STATUS "SOURCE dir "${basetool_SOURCE_DIR})

set(BASE_SRCS
    CityCoding.cpp
    CityCoding.h
    md5.cpp
    md5.h
    StringUtil.cpp
    StringUtil.h
    TestFramework.cpp
    TestFramework.h
    )

add_library(basetool SHARED ${BASE_SRCS}) 

# 指定生成目标
add_executable(CityCoding_test CityCoding_test.cpp)                                                                                                                                 
target_link_libraries(CityCoding_test basetool)
add_test(NAME CityCoding_test COMMAND CityCoding_test)

add_executable(md5_test md5_test.cpp)                                                                                                                                 
target_link_libraries(md5_test basetool)
add_test(NAME md5_test COMMAND md5_test)

add_executable(StringUtil_test StringUtil_test.cpp)                                                                                                                                 
target_link_libraries(StringUtil_test basetool)
add_test(NAME StringUtil_test COMMAND StringUtil_test)


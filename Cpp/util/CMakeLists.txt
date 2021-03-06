cmake_minimum_required (VERSION 2.8)

project (basetool C CXX)

enable_testing()

if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE, "Release")
endif()

set(CMAKE_CXX_FLAGS "-g -D_FILE_OFFSET_BITS=64 -Wall")

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
MESSAGE(STATUS "BINARY dir " ${basetool_BINARY_DIR})
MESSAGE(STATUS "SOURCE dir "${basetool_SOURCE_DIR})

set(BASE_SRCS
    CityCoding.cpp
    md5.cpp
    StringUtil.cpp
    TestFramework.cpp
    UrlCodec.cpp
    Conf.cpp
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

add_executable(UrlCodec_test UrlCodec_test.cpp)                                                                                                                                 
target_link_libraries(UrlCodec_test basetool)
add_test(NAME UrlCodec_test COMMAND UrlCodec_test)

add_executable(Conf_test Conf_test.cpp)                                                                                                                                 
target_link_libraries(Conf_test basetool)
add_test(NAME Conf_test COMMAND Conf_test)
